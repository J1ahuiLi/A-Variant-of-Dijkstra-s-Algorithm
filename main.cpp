#include "graph.h"
#include "minheap.h"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		return -1;
	}
	
	char line[101];
	Graph Gra(argv[1]);
	Gra.read_Inf(argv[2]);
	
	bool flag_valid = false;
	while(fgets(line, 100, stdin) != NULL)
	{
		if(strcmp(line, "stop") == 0)
			break;
		cout << "Query: " << line;

		char command_list[5][100];
		int cmd_pos = 0;
		char *substr= strtok(line, " ");
		while (substr != NULL) 
		{  
			strcpy(command_list[cmd_pos++], substr);			
			substr = strtok(NULL," ");
		}
		int from, to;

		if(strcmp(command_list[0], "find") == 0)
		{
			flag_valid = true;
			for(int i=0;i<sizeof(command_list[1])/sizeof(char);i++)
			{
				if(command_list[1][i]=='.')
				{
					flag_valid = false;
				}
			}		
			for(int i=0;i<sizeof(command_list[2])/sizeof(char);i++)
			{
				if(command_list[2][i]=='.')
				{
					flag_valid = false;
				}
			}		
			from = strtoint(command_list[1]);
			to = strtoint(command_list[2]);
			int flag = strtoint(command_list[3]);
			
			if(!flag_valid || (from < 1 || from > Gra._vexNum || from == to || (flag !=0 && flag != 1)))
				cout << "Error: invalid find query\n";
			else
				Gra.dijkstra(from, to, flag);
		}
		else if((strcmp(command_list[0], "write") == 0) &&(strcmp(command_list[1], "path") == 0) && flag_valid)
		{
			int start = strtoint(command_list[2]);
			int end = strtoint(command_list[3]);
			
			if(start != from || start == end || end < 1 || end > Gra._vexNum)
			{
				printf("Error: invalid source destination pair\n");
			}
			else
			{
				Node* pnode = &Gra.nodes[end];
				int* path = new int[Gra._vexNum];
				int pos = 0;
				bool flag_min_visited = pnode->isvisited;
				bool flag_iscalcul = pnode->iscalcul;
				
				if(pnode->distance != INFINITY)
				{
					double mindisnow = pnode->distance;
					while (pnode != NULL) 
					{
						path[pos] = pnode->data;
						pnode = pnode->previous;
						pos++;
					}
					if(flag_min_visited)
						cout << "Shortest path: <";
					else
						cout << "Path not known to be shortest: <";

					for (int i = pos-1; i >= 0; --i)
					{
						if (i > 0)
							cout << path[i] << ", ";
						else
							cout << path[i] << ">\n";
					}
					printf("The path weight is: %12.4f\n", mindisnow);										
				}

				else
				{
					if((to >= Gra._vexNum) || (to < Gra._vexNum && Gra.nodes[to].iscalcul && flag_iscalcul))
						printf("No %d-%d path exists.\n", start, end);
					else
						printf("No %d-%d path has been computed.\n", start, end);

				}	
				delete[] path;
			}
			
		}
		else if(!flag_valid)
		{
			printf("Error: no path computation done\n");
		}
	}
	return 0;
}