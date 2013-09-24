//
//  Plate.c
//  Conway_App
//
//  Created by FateError on 2013-06-01.
//
//
#include "Plate.h"
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;


// Constructor
Plate::Plate(){
  cap = 51481;
  threshold = cap*3/4;
  //Initialization of cell_slots.
  cell_slots.reserve(cap);
  for(int i = 0 ; i < cap; i++){
    cell_slots[i].reserve(3);
  }
}

// Destructor
Plate::~Plate(){
  // First we clear all data in vectors,done.
  clean();
  // We should never call the destructor of
  // a vector explicitly.
    
}

// See if the cell is alive.
int Plate::get(int x, int y){
  //assert(x < width && x > -1 && y < height && y > -1);
  Cell c;
  c.x_ = x;
  c.y_ = y;
  int index = p_hash(c);
  //printf("before get: %d\n", cell_slots[index][0].live);
  if (cell_slots[index].empty()) {
    //printf("%s\n", "empty");
    return 0;
  }    
  int cx = cell_slots[index][0].c.x_;
  int cy = cell_slots[index][0].c.y_;
  
  if(cx != x || cy != y){
    int end = int(cell_slots[index].size());
    for (int i = 0; i < end; i++) {
      cx = cell_slots[index][i].c.x_;
      cy = cell_slots[index][i].c.y_;
      if (cx == x && cy == y) {
	/*
        printf("aim: %d %d %d\n", x, y, i);
        printf("match: %d %d %d\n", cx, cy, i);
	*/
        return cell_slots[index][i].live;
      }
    }
  }else{
    /*
    printf("aim: %d %d \n", x, y);
    printf("match: %d %d \n", cx, cy);
    */
    return cell_slots[index][0].live;
  }
}

void Plate::dump(int x, int y, int info){
  Cell c;
  c.x_ = x;
  c.y_ = y;
  int index = p_hash(c);
  int cx = cell_slots[index][0].c.x_;
  int cy = cell_slots[index][0].c.y_;
  if(cx!=x || cy!=y){
    int end = int(cell_slots[index].size());
    for(int i = 0; i < end; i++){
      cx = cell_slots[index][i].c.x_;
      cy = cell_slots[index][i].c.y_;
      if(cx == x && cy == y){
	cell_slots[index][i].live = info;
      }
    }
  }else{
    cell_slots[index][0].live = info;
    }
  return;
}


// Hash new cell to its place.
void Plate::push(Cell &cell, int info){
  if(int(cell_slots.size()) >= threshold){
    rehash_size(cap);
    push(cell, info);
  }else{
    int key = p_hash(cell);
    //printf("%d\n",key);
    Grid temp;
    temp.c = cell;
    temp.live = info;
    //if(info == 1){
    //  printf("Push info: x: %d y: %d alive: %d \n", temp.c.x_, temp.c.y_, info);
    //}
    cell_slots[key].push_back(temp);
    //if(info == 1){
      //printf("test %d\n", get(cell.x_, cell.y_));
      //printf("on slots %d %d %d\n", cell_slots[key][0].c.x_,cell_slots[key][0].c.y_,cell_slots[key][0].live);
    // }
  return;
  }
}

// Count neighbours.
int Plate::count(Cell &cell){ 
  int count = 0;
  // count the smallest "9" grids including the cell itself.
  // first get the coordinates of all the nine grids, and find the 
  // cell at that grid.
  //printf("width:%d\nheight:%d\n", width, height);
  for(int i = max(0,cell.x_ -1) ; i < min(width, cell.x_ + 2); i++){    
    for(int j = max(0, cell.y_ -1); j < min(height, cell.y_ + 2); j++){
      //printf("%d %d\n", i, j);
      if(get(i, j) == 1){
        count++;
        //printf("count:%d\n",count);
      }
    }
  }
  // And excluding the cell itself to get the infomation of its neighbours.
  if (get(cell.x_, cell.y_) == 1){
      count--;
    }
   
  return count;
}

// Hash function.
int Plate::p_hash(Cell &cell){
  // Pairing function will uniquelly encode two numbers into a single number,
  // which is a good thing to have "no collision" as a hash function, while 
  // the cons are extremely large number with the growing of size and it takes
  // a lot of memory, for a 300*300 size, the allocated data slots would consume
  // 3mb in memory. :( BAD.
  return (((cell.x_ + cell.y_)*(cell.x_ + cell.y_ + 1)/2) + cell.y_) % cap;
}


void Plate::clean(){
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      Cell c;
      c.x_ = i;
      c.y_ = j;
      int key = p_hash(c);
      cell_slots[key].erase(cell_slots[key].begin(),cell_slots[key].end());
    }
  }
  return;  
}


// In this rehash function, we don't need to erase cells that are settled before
void Plate::rehash_size(int cap){
  cap = cap*3;
  threshold = cap * 3 / 4;
  cell_slots.reserve(cap);
}
/*
int main(){


  Plate p;
  Cell a;
  a.x_ = 12;
  a.y_ = 14;
  p.push(a,1);
  a.x_ = 11;
  a.y_ = 10;
  p.push(a,1);
  p.width = 20;
  p.height = 15;
  p.clean();
  printf("%d\n",p.get(12,14));
  p.dump(12,14,0);
  printf("%d\n",p.get(12,14));
  printf("%d\n", p.get(11,10));

}
*/




