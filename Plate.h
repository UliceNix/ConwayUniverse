//
//  Plate.h
//  Conway_App
//
//  Created by FateError on 2013-06-01.
//
//
#pragma once


#include <vector>
using namespace std;

// Basical cell structure, which contains
// x, y coordinates of a cell in the plate.
struct Cell
{
  int x_;
  int y_;
};

struct Grid
{
  Cell c;
  int live;
};


class Plate
{
 public:
  vector<vector<Grid> > cell_slots; // where we keep the coordiantes of cells.
  int height;
  int width;
  Plate(); // Construction
  ~Plate(); // Destruction
  int get(int x, int y); // See if the cell is alive.
  void push(Cell &cell, int info); // add new cell into the Plate
  int count(Cell &cell); // Count the alive cells around a given cell.
  int p_hash(Cell &cell); // hash function.
  void clean();
  void dump(int x, int y, int info); 
  void rehash_size(int cap);

 private:
  int cap; // the capacity of hashtable.
  int threshold;
  //vector<vector<Grid> > cell_slots; // where we keep the coordiantes of cells.
};
