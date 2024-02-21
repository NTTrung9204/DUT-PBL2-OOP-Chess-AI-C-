#pragma once
#include<iostream>
#include<stack>
#include<vector>

using namespace std;
int Board[8][8] =
{50,10,0,0,0,0,-10,-50,
30,10,0,0,0,0,-10,-30,
35,10,0,0,0,0,-10,-35,
90,10,0,0,0,0,-10,-90,
1000,10,0,0,0,0,-10,-1000,
35,10,0,0,0,0,-10,-35,
30,10,0,0,0,0,-10,-30,
50,10,0,0,0,0,-10,-50};

struct Position{
  int x,y;
};
struct Pos{
  int x,y,value;
};

class Chess{
protected:
  int value;//gia tri cua quan co 10,35,30,50,90,1000
  int index;// 1 la ben minh,-1 la ben may;
public:  
  Chess(){};
  Position P;//vi tri hien tai
  stack<Position> Pnew;//vi tri di chuyen toi duoc
  void die(){
    this->value=-1;
  }
  
  int getValue(){
    return value;
  }
  int getIndex(){
    return index;
  }
  virtual void setValue(){};
   
  
  void setIndex(int n){
    index=n;
  }
  void setP(int m,int n){
    P.x=m;
    P.y=n;
  }
  Position getP(){
    return P;
  }
  void updatePnew(int x1,int y1){
    Position New;
    New.x=x1;
    New.y=y1;
    Pnew.push(New);
  }
  void resetPnew(){
    while (!Pnew.empty())
      Pnew.pop();
  }

  virtual void PositiveMove(){};
};

class Tot:public Chess{
public:
  Tot(){};
  void setValue(){
    this->value=10;
  }
  void PositiveMove(){
    int k=-1*Chess::getIndex();
    if ((Board[P.x][P.y-k]==0)&&(P.y-k>=0)&&(P.y-k<8)) Chess::updatePnew(P.x,P.y-k);
    if ((P.y==1||P.y==6)&&(Board[P.x][P.y-2*k]==0)&&(Board[P.x][P.y-k]==0)&&(P.y-2*k>=0)&&(P.y-2*k<8)) Chess::updatePnew(P.x,P.y-2*k);
    if ((Chess::getIndex()*Board[P.x+1][P.y-k]<0)&&(P.y-k>=0)&&(P.y-k<8)&&(P.x+1<8))  Chess::updatePnew(P.x+1,P.y-k);
    if ((Chess::getIndex()*Board[P.x-1][P.y-k]<0)&&(P.y-k>=0)&&(P.y-k<8)&&(P.x-1>=0))  Chess::updatePnew(P.x-1,P.y-k);
  };
  
};

class Ma:public Chess{
public:
  Ma(){};
  void setValue(){
    this->value=30;
  }
  void PositiveMove(){
    int k=Chess::getIndex();
    if ((Board[P.x+2][P.y+1]==0||Chess::getIndex()*Board[P.x+2][P.y+1]<0)&&(P.x+2<8)&&(P.y+1<8))  Chess::updatePnew(P.x+2,P.y+1);
    if ((Board[P.x+1][P.y+2]==0||Chess::getIndex()*Board[P.x+1][P.y+2]<0)&&(P.x+1<8)&&(P.y+2<8))  Chess::updatePnew(P.x+2,P.y+1);
    if ((Board[P.x-1][P.y-2]==0||Chess::getIndex()*Board[P.x-1][P.y-2]<0)&&(P.x-1>=0)&&(P.y-2>=0))  Chess::updatePnew(P.x-1,P.y-2);
    if ((Board[P.x-2][P.y-1]==0||Chess::getIndex()*Board[P.x-2][P.y-1]<0)&&(P.x-2>=0)&&(P.y-1>=0))  Chess::updatePnew(P.x-2,P.y-1);
    if ((Board[P.x+1][P.y-2]==0||Chess::getIndex()*Board[P.x+1][P.y-2]<0)&&(P.x+1<8)&&(P.y-2>=0))  Chess::updatePnew(P.x+1,P.y-2);
    if ((Board[P.x-1][P.y+2]==0||Chess::getIndex()*Board[P.x-1][P.y+2]<0)&&(P.x-1>=0)&&(P.y+2<8))  Chess::updatePnew(P.x-1,P.y+2);
    if ((Board[P.x-2][P.y+1]==0||Chess::getIndex()*Board[P.x-2][P.y+1]<0)&&(P.x-2>=0)&&(P.y+1<8))  Chess::updatePnew(P.x-2,P.y+1);
     if ((Board[P.x+2][P.y-1]==0||Chess::getIndex()*Board[P.x+2][P.y-1]<0)&&(P.x+2<8)&&(P.y-1>=0))  Chess::updatePnew(P.x+2,P.y-1);
  }
  
};


class Tuong:public Chess{
public:
  Tuong(){};
  void setValue(){
    this->value=35;
  }
  void PositiveMove(){
    int k=Chess::getIndex();
    for (int i=P.x+1,j=P.y+1;(i<8&&j<8);i++,j++){
     
        if (Board[i][j]!=0){
          if (Board[i][j]*k<0) Chess::updatePnew(i,j);
          break;
        }
        Chess::updatePnew(i,j);
      
    }
    for (int i=P.x+1,j=P.y-1;(i<8&&j>=0);i++,j--){
      
        if (Board[i][j]!=0){
          if (Board[i][j]*k<0) Chess::updatePnew(i,j);
          break;
        }
        Chess::updatePnew(i,j);
      
    }
    for (int i=P.x-1,j=P.y-1;(i>=0&&j>=0);i--,j--){
      
        if (Board[i][j]!=0){
          if (Board[i][j]*k<0) Chess::updatePnew(i,j);
          break;
        }
        Chess::updatePnew(i,j);
      
    }
    for (int i=P.x-1,j=P.y+1;(i>=0&&j<8);i--,j++){
      
        if (Board[i][j]!=0){
          if (Board[i][j]*k<0) Chess::updatePnew(i,j);
          break;
        }
        Chess::updatePnew(i,j);
      
    }
  }
};

class Xe:public Chess{
public:
  Xe(){};
  void setValue(){
    this->value=50;
  }
  void PositiveMove(){
    int k=Chess::getIndex();
    for (int i=P.x+1;i<8;i++){
      if (Board[i][P.y]!=0){
        if (Board[i][P.y]*k<0) Chess::updatePnew(i,P.y);
        break;
      }
      Chess::updatePnew(i,P.y);
    }
    for (int i=P.x-1;i>=0;i--){
      if (Board[i][P.y]!=0){
        if (Board[i][P.y]*k<0) Chess::updatePnew(i,P.y);
        break;
      }
      Chess::updatePnew(i,P.y);
    }
    for (int i=P.y+1;i<8;i++){
      if (Board[P.x][i]!=0){
        if (Board[P.x][i]*k<0) Chess::updatePnew(P.x,i);
        break;
      }
      Chess::updatePnew(P.x,i);
    }
    for (int i=P.y-1;i>=0;i--){
      if (Board[P.x][i]!=0){
        if (Board[P.x][i]*k<0) Chess::updatePnew(P.x,i);
        break;
      }
      Chess::updatePnew(P.x,i);
    }
  }
};

class Hau:public Chess{
public:
  Hau(){};
  void setValue(){
    this->value=90;
  }
  void PositiveMove(){
    int k=Chess::getIndex();
    for (int i=P.x+1;i<8;i++){
      if (Board[i][P.y]!=0){
        if (Board[i][P.y]*k<0) Chess::updatePnew(i,P.y);
        break;
      }
      Chess::updatePnew(i,P.y);
    }
    for (int i=P.x-1;i>=0;i--){
      if (Board[i][P.y]!=0){
        if (Board[i][P.y]*k<0) Chess::updatePnew(i,P.y);
        break;
      }
      Chess::updatePnew(i,P.y);
    }
    for (int i=P.y+1;i<8;i++){
      if (Board[P.x][i]!=0){
        if (Board[P.x][i]*k<0) Chess::updatePnew(P.x,i);
        break;
      }
      Chess::updatePnew(P.x,i);
    }
    for (int i=P.y-1;i>=0;i--){
      if (Board[P.x][i]!=0){
        if (Board[P.x][i]*k<0) Chess::updatePnew(P.x,i);
        break;
      }
      Chess::updatePnew(P.x,i);
    }
    for (int i=P.x+1,j=P.y+1;(i<8&&j<8);i++,j++){
     
        if (Board[i][j]!=0){
          if (Board[i][j]*k<0) Chess::updatePnew(i,j);
          break;
        }
        Chess::updatePnew(i,j);
      
    }
    for (int i=P.x+1,j=P.y-1;(i<8&&j>=0);i++,j--){
      
        if (Board[i][j]!=0){
          if (Board[i][j]*k<0) Chess::updatePnew(i,j);
          break;
        }
        Chess::updatePnew(i,j);
      
    }
    for (int i=P.x-1,j=P.y-1;(i>=0&&j>=0);i--,j--){
      
        if (Board[i][j]!=0){
          if (Board[i][j]*k<0) Chess::updatePnew(i,j);
          break;
        }
        Chess::updatePnew(i,j);
      
    }
    for (int i=P.x-1,j=P.y+1;(i>=0&&j<8);i--,j++){
      
        if (Board[i][j]!=0){
          if (Board[i][j]*k<0) Chess::updatePnew(i,j);
          break;
        }
        Chess::updatePnew(i,j);
      
    }

  }
};

class Vua:public Chess{
public:
  Vua(){};
  void setValue(){
    this->value=1000;
  }
  void PositiveMove(){
    int k=Chess::getIndex();
    if ((Board[P.x+1][P.y]*k<=0)&&(P.x+1<8)) Chess::updatePnew(P.x+1,P.y);
    if ((Board[P.x+1][P.y+1]*k<=0)&&(P.x+1<8)&&(P.y+1<8)) Chess::updatePnew(P.x+1,P.y+1);
    if ((Board[P.x+1][P.y-1]*k<=0)&&(P.x+1<8)&&(P.y-1>=0)) Chess::updatePnew(P.x+1,P.y-1);
    if ((Board[P.x-1][P.y]*k<=0)&&(P.x-1>=0)) Chess::updatePnew(P.x-1,P.y);
    if ((Board[P.x-1][P.y+1]*k<=0)&&(P.x-1>=0)&&(P.y+1<8)) Chess::updatePnew(P.x-1,P.y+1);
    if ((Board[P.x-1][P.y-1]*k<=0)&&(P.x-1>=0)&&(P.y-1>=0)) Chess::updatePnew(P.x-1,P.y-1);
    if ((Board[P.x][P.y+1]*k<=0)&&(P.y+1<8)) Chess::updatePnew(P.x,P.y+1);
    if ((Board[P.x][P.y-1]*k<=0)&&(P.y-1>=0)) Chess::updatePnew(P.x,P.y-1);
  }
};

// int main(){
//     Chess *Pos[10];
//     Pos[0]=new Tot;
  
//     Pos[0]->setValue();
//     cout<<Pos[0]->getValue();
//     Pos[0]->setIndex(1);
    
//     Pos[0]->setP(0,1);
//     cout<<Pos[0]->P.x;
//      Pos[0]->PositiveMove();
//      cout<<endl<<Pos[0]->Pnew.size()<<endl;
//      int k=Pos[0]->Pnew.size();
//      stack<Position> P=Pos[0]->Pnew;
//     for (int i=0;i<k;i++){
     
//       cout<<P.top().x<<" "<<P.top().y<<endl;
//       P.pop();
//     }
//     return 0;
// }