/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_map_creator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavlov <apavlov@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:05:24 by apavlov           #+#    #+#             */
/*   Updated: 2019/04/01 13:05:25 by apavlov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

#define	EyeHeight	6

static struct player
{
	struct		xyz { float x,y,z; } where, velocity;
	float		angle, anglesin, anglecos, yaw;
	unsigned	sector;
} player;

static struct sector
{
    float floor, ceil;
    struct xy { float x,y; } *vertex; 
    char *neighbors;           
    unsigned npoints;                 
} *sectors = NULL;

static unsigned NumSectors = 0;
static unsigned NumVertices = 0;
struct xy* vert = NULL, v;

static void LoadData()
{
    FILE* fp = fopen("map-clear.txt", "rt");
    if(!fp) { perror("map-clear.txt"); exit(1); }
    char Buf[256], word[256], *ptr;
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
                for(n=0; n<m; ++n) sect->vertex[n+1]  = vert[num[n]]; // TODO: Range checking
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
}

static void UnloadData()
{
	for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].vertex);
	for(unsigned a=0; a<NumSectors; ++a) free(sectors[a].neighbors);
	free(sectors);
	sectors = NULL;
	NumSectors = 0;
	free(vert);
}

int		write_to_file(t_map map, char *name, t_player mplayer)
{
	int		fd;
	int		i;

	if (open(name, O_EXCL) > 0) //if exist
		fd = open(name, O_WRONLY);
	else
		fd = open(name, O_CREAT | O_WRONLY);
	if (!fd)
		return (0);
	printf("%s %i", name, fd);

	write(fd, &map.num_sect, sizeof(Uint32));
	write(fd, &map.num_vert, sizeof(Uint32));

	write(fd, map.vertex, sizeof(t_vertex) * map.num_vert);

	i = -1;
	while (++i < map.num_sect)
	{
		write(fd, &map.sectors[i].num, sizeof(Uint32));
		write(fd, &map.sectors[i].num_vert, sizeof(Uint32));
		write(fd, map.sectors[i].vert, sizeof(t_vertex) * map.sectors[i].num_vert);
		//write(fd, map.sectors[i].lines, sizeof(t_line) * map.sectors[i].num_vert); //this one is unusable here
		write(fd, map.sectors[i].neighbors, sizeof(char) * map.sectors[i].num_vert);
		write(fd, &map.sectors[i].floor_z, sizeof(Uint32));
		write(fd, &map.sectors[i].ceil_z, sizeof(Uint32));
		write(fd, &map.sectors[i].floor_plane, sizeof(t_plane));
		write(fd, &map.sectors[i].ceil_plane, sizeof(t_plane));
	}

	write(fd, &mplayer, sizeof(t_player));
	close(fd);
	return (1);
}

int		main(int argc, char **argv)
{
	(void)argc;
	t_map		map;
	t_player	myPlayer;
	int		i;
	int		j;

	LoadData();

	map.num_sect = NumSectors;
	map.num_vert = NumVertices;

	map.vertex = (t_vertex*)malloc(sizeof(t_vertex) * NumVertices);
	i = -1;
	while (++i < map.num_vert)	//Copy vertices
	{
		map.vertex[i].x = vert[i].x;
		map.vertex[i].y = vert[i].y;
	}

	map.sectors = (t_sector*)malloc(sizeof(t_sector) * NumSectors);
	i = -1;
	while (++i < map.num_sect)	//Copy sectors data
	{
		map.sectors[i].num = i;
		map.sectors[i].num_vert = sectors[i].npoints;
		map.sectors[i].vert = (t_vertex*)malloc(sizeof(t_vertex) * map.sectors[i].num_vert);
		j = -1;
		while (++j < map.sectors[i].num_vert)
		{
			map.sectors[i].vert[j].x = sectors[i].vertex[j].x;
			map.sectors[i].vert[j].y = sectors[i].vertex[j].y;
		}
		map.sectors[i].ceil_z = sectors[i].ceil;
		map.sectors[i].floor_z = sectors[i].floor;
		map.sectors[i].neighbors = (char*)malloc(sizeof(char) * map.sectors[i].num_vert);
		j = -1;
		while (++j < map.sectors[i].num_vert)
			map.sectors[i].neighbors[j] = (sectors[i].neighbors[j]);
	}

	myPlayer.coord.x = player.where.x;
	myPlayer.coord.y = player.where.y;
	myPlayer.coord.z = player.where.z;
	myPlayer.sector = player.sector;
	myPlayer.angle = player.angle;
	myPlayer.angle_z = player.yaw;
	myPlayer.anglecos = player.anglecos;
	myPlayer.anglesin = player.anglesin;

	write_to_file(map, argv[1], myPlayer);

	i = -1;
	while (++i < map.num_sect)
	{
		free(map.sectors[i].vert);
		free(map.sectors[i].neighbors);
	}
	free(map.sectors);
	free(map.vertex);

	UnloadData();
}