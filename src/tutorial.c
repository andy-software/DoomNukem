/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:14:46 by apavlov           #+#    #+#             */
/*   Updated: 2019/03/22 13:14:46 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>

/* Define window size */
#define W 1200
#define H 800
/* Define various vision related constants */
#define EyeHeight  6    // Camera height from floor when standing
#define DuckHeight 2.5  // And when crouching
#define HeadMargin 1    // How much room there is above camera before the head hits the ceiling
#define KneeHeight 2    // How tall obstacles the player can simply walk over without jumping
#define hfov (0.5f*W)  // Affects the horizontal field of vision
#define vfov (0.2f*H)    // Affects the vertical field of vision

/* Sectors: Floor and ceiling height; list of edge vertices and neighbors */
static struct sector
{
    float floor, ceil;
    struct xy { float x,y; } *vertex; // Each vertex has an x and y coordinate
    signed char *neighbors;           // Each edge may have a corresponding neighboring sector
    unsigned npoints;                 // How many vertexes there are
} *sectors = NULL;
static unsigned NumSectors = 0;

/* Player: location */
static struct player
{
    struct xyz { float x,y,z; } where,      // Current position
                                velocity;   // Current motion vector
    float angle, anglesin, anglecos, yaw;   // Looking towards (and sin() and cos() thereof)
    unsigned sector;                        // Which sector the player is currently in
} player;


static unsigned NumVertices = 0;
// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
/* Project our ceiling & floor heights into screen coordinates (Y coordinate) */
#define Yaw(y,z) (y + z*player.yaw)
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

static void LoadData()
{
    FILE* fp = fopen("map-clear.txt", "rt");
    if(!fp) { perror("map-clear.txt"); exit(1); }
    char Buf[256], word[256], *ptr;
    struct xy* vert = NULL, v;
    int n, m = 0;
    while(fgets(Buf, sizeof Buf, fp))
        switch(sscanf(ptr = Buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
        {
            case 'v': // vertex
                for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
                    { vert = realloc(vert, ++NumVertices * sizeof(*vert)); vert[NumVertices-1] = v; }
                break;
            case 's': // sector
                sectors = realloc(sectors, ++NumSectors * sizeof(*sectors));
                struct sector* sect = &sectors[NumSectors-1];
                int* num = NULL;
                sscanf(ptr += n, "%f%f%n", &sect->floor,&sect->ceil, &n);
                for(m=0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
                    { num = realloc(num, ++m * sizeof(*num)); num[m-1] = word[0]=='x' ? -1 : atoi(word); }
                sect->npoints   = m /= 2;
                sect->neighbors = malloc( (m  ) * sizeof(*sect->neighbors) );
                sect->vertex    = malloc( (m+1) * sizeof(*sect->vertex)    );
                for(n=0; n<m; ++n) sect->neighbors[n] = num[m + n];
                for(n=0; n<m; ++n) sect->vertex[n+1] = vert[num[n]]; // TODO: Range checking
                sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
                free(num);
                break;
            case 'p':; // player
                float angle;
                sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle,&n);
                player = (struct player) { {v.x, v.y, 0}, {0,0,0}, angle,0,0,0, n }; // TODO: Range checking
                player.where.z = sectors[player.sector].floor + EyeHeight;
        }
    fclose(fp);
    free(vert);
}

struct xy	intersect(struct xy d1, struct xy d2, struct xy d3, struct xy d4) //find the coord dot of intersection of line {d1, d2} and line {d3, d4}
{
	float	lenght;
	float	n1;
	float	n2;

	n1 = vxs(d1.x, d1.y, d2.x, d2.y);
	n2 = vxs(d3.x, d3.y, d3.x, d3.y);
	lenght = vxs(d1.x - d2.x, d1.y - d2.y, d3.x - d4.x, d3.y - d4.y);
	return ((struct xy){vxs(n1, d1.x - d2.x, n2, d3.x - d4.x) / lenght,
		vxs(n1, d1.y - d2.y, n2, d3.y - d4.y) / lenght});
}

static void UnloadData()
{
    for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].vertex);
    for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].neighbors);
    free(sectors);
    sectors    = NULL;
    NumSectors = 0;
}

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
static void vline(int x, int y1,int y2, int top,int middle,int bottom)
{
    int *pix = (int*) surface->pixels;
    y1 = clamp(y1, 0, H-1);
    y2 = clamp(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1 + 1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2*W+x] = bottom;
    }
}

/* MovePlayer(dx,dy): Moves the player by (dx,dy) in the map, and
 * also updates their anglesin/anglecos/sector properties properly.
 */
static void MovePlayer(float dx, float dy)
{
    float px = player.where.x, py = player.where.y;
    /* Check if this movement crosses one of this sector's edges
     * that have a neighboring sector on the other side.
     * Because the edge vertices of each sector are defined in
     * clockwise order, PointSide will always return -1 for a point
     * that is outside the sector and 0 or 1 for a point that is inside.
     */
    const struct sector* const sect = &sectors[player.sector];
    const struct xy* const vert = sect->vertex;
    for(unsigned s = 0; s < sect->npoints; ++s)
        if(sect->neighbors[s] >= 0
        && IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
        && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
        {
            player.sector = sect->neighbors[s];
            break;
        }
    player.where.x += dx;
    player.where.y += dy;
}

static void DrawScreen()
{
    struct item { int sectorno,sx1,sx2; } now = {player.sector, 0 , W - 1};
    int ztop[W]={0}, zbottom[W];
    for(unsigned x=0; x<W; ++x)
        zbottom[x] = H-1;
    float pcos = player.anglecos;
    float psin = player.anglesin;

    const struct sector* const sect = sectors + now.sectorno;
    for(unsigned s = 0; s < sect->npoints; ++s)
    {
        float vx1 = sect->vertex[s].x - player.where.x;
        float vy1 = sect->vertex[s].y - player.where.y;
        float vx2 = sect->vertex[s+1].x - player.where.x;
        float vy2 = sect->vertex[s+1].y - player.where.y;
        float tx1 = vx1 * psin - vy1 * pcos;
        float ty1 = vx1 * pcos + vy1 * psin;
        float tx2 = vx2 * psin - vy2 * pcos;
        float ty2 = vx2 * pcos + vy2 * psin;
        if(ty1 <= 0 && ty2 <= 0)
            continue;
        if(ty1 <= 0 || ty2 <= 0)
        {
            #define neary 1e-3f
            #define fary  5.f
            #define nearside  1e-4f
            #define farside  20.f
            struct xy i1 = intersect((struct xy){tx1,ty1},(struct xy){tx2,ty2}, (struct xy){-nearside,neary}, (struct xy){-farside,fary});
            struct xy i2 = intersect((struct xy){tx1,ty1},(struct xy){tx2,ty2},  (struct xy){nearside,neary},  (struct xy){farside,fary});
            if(ty1 < 0) 
            { 
                if(i1.y > 0) 
                {
                    tx1 = i1.x; 
                    ty1 = i1.y; 
                }
                else 
                {
                    tx1 = i2.x; 
                    ty1 = i2.y; 
                }
            }
            if(ty2 < 0) 
            { 
               if(i1.y > 0) 
               { 
                   tx2 = i1.x; 
                   ty2 = i1.y; 
               } 
               else 
               { 
                   tx2 = i2.x; 
                   ty2 = i2.y; } 
            }
        }
        float xscale1 = hfov / ty1;
        float xscale2 = hfov / ty2;
        float zscale1 = vfov / ty1;
        float zscale2 = vfov / ty2;
        int x1 = W/2 - (int)(tx1 * xscale1);
        int x2 = W/2 - (int)(tx2 * xscale2);
        if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2)
            continue; 
        float zceil = sect->ceil - player.where.z;
        float zfloor = sect->floor - player.where.z;
        int neighbor = sect->neighbors[s];

        float nzceil = 0;
        float nzfloor = 0;
        if(neighbor >= 0)
        {
             nzceil  = sectors[neighbor].ceil  - player.where.z;
             nzfloor = sectors[neighbor].floor - player.where.z;
        }
        int z1a  = H/2 - (int)((zceil + ty1 * player.yaw) * zscale1);
        int z1b = H/2 - (int)((zfloor + ty1 * player.yaw) * zscale1);
        int z2a  = H/2 - (int)((zceil + ty2 * player.yaw) * zscale2);
        int z2b = H/2 - (int)((zfloor + ty2 * player.yaw) * zscale2);

        int nz1a = H/2 - (int)((nzceil + ty1 * player.yaw) * zscale1);
        int nz1b = H/2 - (int)((nzfloor + ty1 * player.yaw) * zscale1);
        int nz2a = H/2 - (int)((nzceil + ty2 * player.yaw) * zscale2);
        int nz2b = H/2 - (int)((nzfloor + ty2 * player.yaw) * zscale2);

        int beginx = max(x1, now.sx1);
        int endx = min(x2, now.sx2);

        for(int x = beginx; x <= endx; ++x)
        {
            int za = (x - x1) * (z2a - z1a) / (x2 - x1) + z1a;
            za = clamp(za, ztop[x],zbottom[x]);
            int zb = (x - x1) * (z2b - z1b) / (x2 - x1) + z1b;
            zb = clamp(zb, ztop[x], zbottom[x]);

            vline(x, ztop[x], za - 1, 0x111111 ,0x222222,0x111111);
            vline(x, zb + 1, zbottom[x], 0x0000FF,0x0000AA,0x0000FF);

            if(neighbor >= 0)
            {
                //vline(x, za, zb, 0x00AAAA, 0x00BB00, 0xAACC00);
                /* Same for _their_ floor and ceiling */
                int nza = (x - x1) * (nz2a - nz1a) / (x2 - x1) + nz1a;
                nza = clamp(nza, ztop[x],zbottom[x]);
                int nzb = (x - x1) * (nz2b - nz1b) / (x2 - x1) + nz1b;
                nzb = clamp(nzb, ztop[x],zbottom[x]);
                /* If our ceiling is higher than their ceiling, render upper wall */
                vline(x, za, nza - 1, 0, 0x0F0F0F, 0); // Between our and their ceiling
                ztop[x] = clamp(max(za, nza), ztop[x], H-1);   // Shrink the remaining window below these ceilings
                /* If our floor is lower than their floor, render bottom wall */
                vline(x, nzb + 1, zb, 0, 0xAFBF0F, 0); // Between their and our floor
                zbottom[x] = clamp(min(zb, nzb), 0, zbottom[x]); // Shrink the remaining window above these floors
            }
            else
                vline(x, za, zb, 0, 0xAAAAAA, 0);
                // /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                // unsigned r = 0x010101 * (255-z);
                
         }
    }
}

int main()
{
    LoadData();
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetWindowGrab(window, 1);
	SDL_SetRelativeMouseMode(1);

    int wsad[4]={0,0,0,0}, ground=1, falling=0, moving=0, ducking=0;
    float yaw = 0;
    while (1)
    {
        bzero(surface->pixels, surface->h * surface->w);
        DrawScreen();

        /* Vertical collision detection */
        float eyeheight = ducking ? DuckHeight : EyeHeight;
        ground = !falling;
        if(falling)
        {
            player.velocity.z -= 0.02f; /* Add gravity */
            float nextz = player.where.z + player.velocity.z;
            if(player.velocity.z < 0 && nextz  < sectors[player.sector].floor + eyeheight) // When going down
            {
                /* Fix to ground */
                player.where.z    = sectors[player.sector].floor + eyeheight;
                player.velocity.z = 0;
                falling = 0;
                ground  = 1;
            }
            else if(player.velocity.z > 0 && nextz > sectors[player.sector].ceil) // When going up
            {
                /* Prevent jumping above ceiling */
                player.velocity.z = 0;
                falling = 1;
            }
            if(falling)
            {
                player.where.z += player.velocity.z;
                player.yaw -= 0.5;
                moving = 1;
            }
        }
        /* Horizontal collision detection */
        if(moving)
        {
            float px = player.where.x,    py = player.where.y;
            float dx = player.velocity.x, dy = player.velocity.y;

            const struct sector* const sect = &sectors[player.sector];
            const struct xy* const vert = sect->vertex;
            /* Check if the player is about to cross one of the sector's edges */
            for(unsigned s = 0; s < sect->npoints; ++s)
                if(IntersectBox(px,py, px+dx,py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y)
                && PointSide(px+dx, py+dy, vert[s+0].x, vert[s+0].y, vert[s+1].x, vert[s+1].y) < 0)
                {
                    /* Check where the hole is. */
                    float hole_low  = sect->neighbors[s] < 0 ?  9e9 : max(sect->floor, sectors[sect->neighbors[s]].floor);
                    float hole_high = sect->neighbors[s] < 0 ? -9e9 : min(sect->ceil,  sectors[sect->neighbors[s]].ceil );
                    /* Check whether we're bumping into a wall. */
                    if(hole_high < player.where.z+HeadMargin
                    || hole_low  > player.where.z-eyeheight+KneeHeight)
                    {
                        /* Bumps into a wall! Slide along the wall. */
                        /* This formula is from Wikipedia article "vector projection". */
                        float xd = vert[s+1].x - vert[s+0].x, yd = vert[s+1].y - vert[s+0].y;
                        float k = (dx*xd + yd*dy) / (xd*xd + yd*yd);
                        dx = xd * k;
                        dy = yd * k;
                    }
                }
            MovePlayer(dx, dy);
            falling = 1;
        }

        SDL_Event ev;
        while(SDL_PollEvent(&ev))
            switch(ev.type)
            {
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    switch(ev.key.keysym.sym)
                    {
                        case 'w': wsad[0] = falling ? 0 : ev.type==SDL_KEYDOWN; break;
                        case 's': wsad[1] = falling ? 0 : ev.type==SDL_KEYDOWN; break;
                        case 'a': wsad[2] = falling ? 0 : ev.type==SDL_KEYDOWN; break;
                        case 'd': wsad[3] = falling ? 0 : ev.type==SDL_KEYDOWN; break;
                        case 27: exit(0); break;
                        case ' ': /* jump */
                            if(ground) { player.velocity.z += 0.5; falling = 1; }
                            break;
                        case SDLK_LCTRL: /* duck */
                        case SDLK_RCTRL: ducking = ev.type==SDL_KEYDOWN; falling=1; break;
                        default: break;
                    }
                    break;
                case SDL_QUIT: goto done;
            }

        /* mouse aiming */
        int x,y;
        SDL_GetRelativeMouseState(&x,&y);

        player.angle += x * 0.03f;
        yaw          = clamp(yaw - y*0.05f, -5, 5);
        player.yaw   = yaw - player.velocity.z*0.5f;
        player.anglesin = sinf(player.angle);
        player.anglecos = cosf(player.angle);
        

        float move_vec[2] = {0.f, 0.f};
        if(wsad[0]) { move_vec[0] += player.anglecos*0.2f; move_vec[1] += player.anglesin*0.2f; }
        if(wsad[1]) { move_vec[0] -= player.anglecos*0.2f; move_vec[1] -= player.anglesin*0.2f; }
        if(wsad[2]) { move_vec[0] += player.anglesin*0.2f; move_vec[1] -= player.anglecos*0.2f; }
        if(wsad[3]) { move_vec[0] -= player.anglesin*0.2f; move_vec[1] += player.anglecos*0.2f; }
        moving = wsad[0] || wsad[1] || wsad[2] || wsad[3];
        float acceleration = 0.2;

        player.velocity.x = player.velocity.x * (1-acceleration) + move_vec[0] * acceleration;
        player.velocity.y = player.velocity.y * (1-acceleration) + move_vec[1] * acceleration;

        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }
done:
    UnloadData();
    SDL_Quit();
    return 0;
}
