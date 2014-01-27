//
//  Conway.c
//  Conway_App
//
//  Created by FateError on 2013-06-01.
//
//

#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <string>
#include "Plate.h"

int max_width = 0; // Global variables are used to keep record of 

int max_height = 0;// the input size.

// return the status of the cell in the plate.
bool alive(Plate* p, Cell c){

  if(c.x_>=0 && c.x_ < p->width && c.y_>=0 && c.y_ < p->height){

    return p->get(c.x_, c.y_);

  }else{

    printf("Invalid Coordinates, please check again!\n");

    return false;

  }

}

// count the number of neighbours around a cell in 9-grid space.
int count_neighbours(Plate* p, int x, int y){

  if(x>=0 && x < p->width && y>=0 && y < p->height){

    Cell temp;

    temp.x_ = x;

    temp.y_ = y;

    return p->count(temp);

  }else{

    printf("Invalid Coordinates, please check again!\n");

    return 0;
  }

}

// count the number of alive cells in a part of size height * width in the plate.
int count_plate(Plate* cur, int hs, int he, int ws, int we){

  int total = 0;

  for (int j = hs;  j < he; j++) {

    for(int i = ws; i < we; i++){

      if (cur->get(i,j) == 1) {

	total++;

      }

    } 

  }

  return total;

}

// print the part of (height * width) in the plate.
void  print(Plate* cur, int hs, int he, int ws, int we){
  // iterate around the plate.

  for (int j = hs;  j < he; j++) {

    for(int i = ws; i < we; i++){

      if (cur->get(i,j) == 1) {

        printf("%s", "*"); // print the cell if it's alive

      }else{

        printf("%s", " "); // otherwise print a whitespace

      }

    }

    printf("%s\n",""); // when finishing a line remember to change to a new line.

  }

  return;
}

// is_number tells if a string is an integer.

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


// generate the next generation based on the current plate.
void next_config(Plate* cur, Plate* next){

  for(int row = 0; row < cur->width; row++){

    for(int col = 0; col < cur->height; col++){

      Cell temp;

      temp.x_ = row;

      temp.y_ = col;

      int k  = count_neighbours(cur, row,col);

      int info = 0;

      if(k==3){

        info = 1;

      }else if(k == 2){

        info = cur->get(row, col);

      }else if(0 <= k && k <= 8){

        info = 0;

      }

      next->push(temp, info);

    }

  }

  return;

}

// Display the conway universe with the most number of cells in some 80 * 20 window.
int display(Plate* p){

  int max_part = 0;
  
  int dis_height = 0;
  
  int dis_width = 0;
  
  int total = count_plate(p, 0, p->height, 0, p->width);
  
  // the whole file is within the size of 80 * 20
  if(0 < p->width && p->width <= 80 && 0< p->height && p->height <= 20){

    print(p, 0, p->height, 0, p->width);

    return 0;

  }else if( p->width > 80 && p->height > 20){
    // the whole file is out of 80 * 20
    printf("%s\n", "cut version");
    
    printf("%d %d\n", p->width, p->height);

    for(int i = 0; i + 80 < p->width; i++){

      for(int j = 0; j + 20 < p->height; j++){

	int count_part = count_plate(p, j, j+20, i, i+80);

	if(count_part > max_part){

	  max_part = count_part;

	  dis_height = j;

	  dis_width = i;

	}	

      }

    }
    int height_e = 20;

    if(dis_height + 20 > height_e){

      height_e = dis_height + 20;

    }

    int width_e = 80;

    if(dis_width + 80 > width_e){

      width_e = dis_width + 80;

    }

    printf("width: %d ~ %d, height: %d ~ %d \n",dis_width, width_e, dis_height, height_e );

    printf("part_cell: %d total: %d\n", max_part, total);

    print(p, dis_height, height_e, dis_width, width_e);

    return (max_part > total);  

  } else if( p->width <= 80 && p->height > 20){
    // the whole file is within 80 but larger than 20. (j)
    printf("%s\n", "cut version");
    
    printf("%d %d\n", p->width, p->height);

    for(int j = 0; j + 20 < p->height; j++){

      int count_part = count_plate(p, j, j+20, 0, p->width);
      
      if(count_part > max_part){
	
	max_part = count_part;
	
	dis_height = j;

      }	

    }
    
    int height_e = 20;

    if(dis_height + 20 > height_e){

      height_e = dis_height + 20;

    }

    printf("width: %d ~ %d, height: %d ~ %d \n", 0, 80, dis_height, height_e);

    printf("part_cell: %d total: %d\n", max_part, total);

    print(p, dis_height, height_e, 0, 80);

    return (max_part >= total); 
 
  } else if( p->width > 80 && p->height <= 20){
    // within 20 in height but out of 80 in width.(i)
    printf("%s\n", "cut version");
    
    printf("%d %d\n", p->width, p->height);

    for(int i = 0; i + 80 < p->width; i++){

      int count_part = count_plate(p, 0, p->height, i, i + 80);
      
      if(count_part > max_part){
	
	max_part = count_part;
	
	dis_width = i;

      }	

    }


    int width_e = 80;

    if(dis_width + 80 > width_e){

      width_e = dis_width + 80;

    }

    printf("width: %d ~ %d, height: %d ~ %d \n",dis_width, width_e, 0, 20);

    printf("part_cell: %d total: %d\n", max_part, total);

    print(p, 0, 20, dis_width, width_e);

    return (max_part > total);  

  } 

}

// Take in the input file and initialize the plate.
void initialize(Plate* p, FILE* fp){

  char c;

  int width = -1;

  int height = 0;

  c = fgetc(fp);

  while(c != EOF){

    width++;

    //printf("%c", c);

    if(c == '*')

    {

      Cell temp;

      temp.x_ = width;

      temp.y_ = height;

      int live = 1;

      p->push(temp, live);

    }else if (c == 012){

      if(width > max_width){

        max_width = width;

      }

      width = -1;

      height++;

    }

    c = fgetc(fp);

  }

  max_height = height;

  p->height = max_height;

  p->width = max_width;

  if(fclose(fp)){

    perror("Encountered fclose error!\n");

    exit(10);

  }

  /*
   int test = p->get(2,2);
   printf("%d\n",test);
   uncomment this section to do test
   */

}


int main(int argv, char* args[]){

  Plate p;

  Plate *pp = &p;

  Plate *pd;

  Plate decoy;

  pd = &decoy;

  if(argv < 2){ 

    printf("No input file, please make sure you entered the file name!\n");

    exit(10);    
  
  }else if(argv == 2){    

    char* fname = args[1];

    printf("%s\n",fname);

    FILE *fp = fopen(fname, "r+");

    if (!fp){

      perror("Encountered fopen error\n");

      exit(10);

    }else{

      initialize(pp, fp);
      
      //print(pp, pp->height, pp->width);
      
      display(pp);
      
      pd->height = pp->height;
      
      pd->width = pp->width;

    }

  }else if(argv == 3){

    char* fname = args[1];    

    int n = atoi(args[2]);

    FILE *fp = fopen(fname, "r+");

    if (!fp){

      perror("Encountered fopen error\n");

      exit(10);

    }else{

      initialize(pp,fp);

      pd->height = pp->height;

      pd->width = pp->width;

      for(int i = 0; i < n; i++){

	/*
	printf("BEFORE");
	print(pp);
	*/

	next_config(pp, pd);

	//printf("%s\n","next config");

	Plate *temp;  // swap two pointers.
	temp = pp;
	pp = pd;
	pd = temp;
	pd->clean();

	/*
	printf("%s\n","SAME AS PD");
	print(pp);
	printf("%s\n", "CLEAN");
	print(pd);
	*/

      }

      // print(pp, pp->height, pp->width);
      display(pp);
    }

  }else{

    printf("%s\n","Too many arguments, please specify the input file and/or the generation number.Please try again.");

    exit(10);

  }
  
  cout<<"Welcome to conway universe."<<endl;
  
  bool quit = false;

  while(!quit){

    cout<<"Enter an integer n to see the next n-th filial generation"<<endl;

    cout<<"Enter 'q' to terminate"<<endl;

    string line;

    getline(cin, line);


    if(line.compare("") == 0){

      next_config(pp, pd);

      Plate *temp;

      temp = pp;

      pp = pd;

      pd = temp;

      pd->clean();

      //printf("(%d, %d)\n", pp->height, pp->width);
      //print(pp, pp->height, pp->width);
      display(pp);
      
    }else if(line.compare("q") == 0){

      quit = true;
      
      exit(10);

    }else{

      if(is_number(line)){

	int n = atoi(line.c_str());

	for(int i = 0; i < n; i++){

	  /*
	    printf("BEFORE");
	    print(pp);
	  */

	  next_config(pp, pd);

	  //printf("%s\n","next config");

	  Plate *temp;

	  temp = pp;

	  pp = pd;

	  pd = temp;

	  pd->clean();

	  /*
	    printf("%s\n","SAME AS PD");
	    print(pp);
	    printf("%s\n", "CLEAN");
	    print(pd);
	  */

	}

	//print(pp, pp->height, pp->width);
	display(pp);
      }else{

	cout<<"Invalid input, please try again!"<<endl;

      }

    }

  }

}

