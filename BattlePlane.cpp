#include <cstdlib>
#include <iostream>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>
#include <unistd.h>
#include <dos.h>
using namespace std;
#define randreset srand(time(NULL))
#define n 10
int mat[4][n][n];
/*
0-PC planes
1-PC hits
2-User planes
3-User hits
*/
void afismat(int k)
{
    cout<<"    ";
    for(int i=0;i<n;i++)
        cout<<"["<<i<<"]";
    cout<<"\n";
    for(int i=0;i<n;i++)
    {
        cout<<"["<<i<<"] ";
        for(int j=0;j<n;j++)
        {
            if(k%2==0)
            {
                switch(mat[k][i][j])
                {
                    case 0: cout<<"   ";break;
                    case 1: cout<<"[+]";break;
                    case 2:cout<<"[ ]";break;
                    default:break;
                }
            }
            else
            {
                 switch(mat[k][i][j])
                {
                    case 0: cout<<"_";break;
                    case 1: cout<<"X";break;
                    case 2:cout<<"O";break;
                    default:break;
                }
            }
        }
        cout<<"\n";
    }
}

bool testPlane(int x,int y,int dir,int k)
{
     if(mat[k][x][y]!=0) return false; //head
     switch(dir)//out of bounds
            {
                case 1: if(x-3<0 || y+1>=n || y-1<0) return false;break;
                case 2: if(x-1<0 || y+3>=n || x+1>=n) return false;break;
                case 3: if(x+3>=n || y+1>=n || y-1<0) return false;break;
                case 4: if(x-1<0 || y-3<0 || x+1>=n) return false;break;
                default: break;
            }
        switch(dir)//interference
        {
            case 1:
                if(mat[k][x-1][y]!=0 || mat[k][x-1][y-1]!=0 || mat[k][x-1][y+1]!=0) return false;//Wings
                if(mat[k][x-2][y]!=0) return false;//body
                if(mat[k][x-3][y]!=0 || mat[k][x-3][y-1]!=0 || mat[k][x-3][y+1]!=0) return false;//Tail
                break;
            case 2:
                if(mat[k][x][y+1]!=0 || mat[k][x-1][y+1]!=0 || mat[k][x+1][y+1]!=0) return false;//Wings
                if(mat[k][x][y+2]!=0) return false;//body
                if(mat[k][x][y+3]!=0 || mat[k][x-1][y+3]!=0 || mat[k][x+1][y+3]!=0) return false;//Tail
                break;
            case 3:
                if(mat[k][x+1][y]!=0 || mat[k][x+1][y-1]!=0 || mat[k][x+1][y+1]!=0) return false;//Wings
                if(mat[k][x+2][y]!=0) return false;//body
                if(mat[k][x+3][y]!=0 || mat[k][x+3][y-1]!=0 || mat[k][x+3][y+1]!=0) return false;//Tail
                break;
            case 4:
                if(mat[k][x][y-1]!=0 || mat[k][x-1][y-1]!=0 || mat[k][x+1][y-1]!=0) return false;//Wings
                if(mat[k][x][y-2]!=0) return false;//body
                if(mat[k][x][y-3]!=0 || mat[k][x-1][y-3]!=0 || mat[k][x+1][y-1]!=0) return false;//Tail
                break;
            
        }
        return true;
            
}
void InsertPlane(int x,int y,int dir,int k)
{
    mat[k][x][y]=1;
    switch(dir)
    {
        case 1:
        {
            // Wings
               mat[k][x-1][y]=2;
               mat[k][x-1][y-1]=2;
               mat[k][x-1][y+1]=2;
            //
            //Body
               mat[k][x-2][y]=2;
            //
            //Tail
               mat[k][x-3][y]=2;
               mat[k][x-3][y-1]=2;
               mat[k][x-3][y+1]=2;
            //
            break;
        }
        case 2:
        {
            // Wings
               mat[k][x][y+1]=2;
               mat[k][x-1][y+1]=2;
               mat[k][x+1][y+1]=2;
            //
            //Body
               mat[k][x][y+2]=2;
            //
            //Tail
               mat[k][x][y+3]=2;
               mat[k][x-1][y+3]=2;
               mat[k][x+1][y+3]=2;
            //
            break;
        }
        case 3:
         {
               // Wings
               mat[k][x+1][y]=2;
               mat[k][x+1][y-1]=2;
               mat[k][x+1][y+1]=2;
            //
            //Body
               mat[k][x+2][y]=2;
            //
            //Tail
               mat[k][x+3][y]=2;
               mat[k][x+3][y-1]=2;
               mat[k][x+3][y+1]=2;
            //
            break;
        }
        case 4:
         {   // Wings
               mat[k][x][y-1]=2;
               mat[k][x-1][y-1]=2;
               mat[k][x+1][y-1]=2;
            //
            //Body
               mat[k][x][y-2]=2;
            //
            //Tail
               mat[k][x][y-3]=2;
               mat[k][x-1][y-3]=2;
               mat[k][x+1][y-3]=2;
            //
            break;
        }  
    }
}
void GeneratePcPlane()
{
    int x,y,dir;
    for(int q=0;q<3;q++)
    {
        bool good=false;
        while(!good)
        {
            randreset;
            x=rand()%n;
            y=rand()%n;
            dir=rand()%4+1;
            good=testPlane(x,y,dir,0);
        }
        InsertPlane(x,y,dir,0);
    }
}

void UserInsertPlane()
{
    int nrav=1,x,y,dir;
    while(nrav<=3)
    {
        bool reusit=false;
        while(!reusit)
        {
            reusit=true;
            afismat(2);
            cout<<"Set the position for the head of plane "<<nrav<<":\n";
            cout<<"x:";cin>>x;
            cout<<"y:";cin>>y;
            if(x>=n || x<0 || y>=n || y<0) {reusit=false;cout<<"Out of bounds";Sleep(1000);system("cls");break;}
            else
            {
                cout<<"Chose the direction the plane goes :\n1-down\n2-left\n3-up\n4-right\n";
                cin>>dir;
                reusit=testPlane(x,y,dir,2);
                if(!reusit) {cout<<"The plane overlaps with another or is out of bounds. Please try again";system("cls");Sleep(2000);}
                else{ InsertPlane(x,y,dir,2); nrav++; system("cls");}
            }
        }
        
    }
}
            

int main(int argc, char *argv[])
{
    cout<<"The Computer is positioning its planes. Please wait.\n";
    GeneratePcPlane();
    cout<<"The Computer has positioned the planes. Your turn:\n";
    UserInsertPlane();
    cout<<"\nPC:\n";
    afismat(0);
    cout<<"\nUser:\n";
    afismat(2);
    system("PAUSE");
    return EXIT_SUCCESS;
}
