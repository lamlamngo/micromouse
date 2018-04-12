import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

public class Maze{
    private final int X;
    private final int Y;
    private Cell[][] maze;
    private int[] orientation = {1,2,4,8}; //backward: 1 forward: 2 right: 4 left: 8

    public Maze(int x, int y){
        this.X = x;
        this.Y = y;
        maze = new Cell[x][y];
    }

    public void generate() {
        Random rand = new Random();
        int x = rand.nextInt(X);
        int y = rand.nextInt(Y);
        recurseGenerate(x,y);
    }

    private void recurseGenerate(int x, int y){
        if (isValid(x,y)){
            ArrayList<Cell> neigh = new ArrayList<>();
            if (isValid(x+1,y) && !maze[x+1][y].isVisited()){
                neigh.add(maze[x+1][y]);
            }
            if (isValid(x-1,y) && !maze[x-1][y].isVisited()){
                neigh.add(maze[x-1][y]);
            }
            if (isValid(x,y+1) && !maze[x][y+1].isVisited()){
                neigh.add(maze[x][y+1]);
            }
            if (isValid(x,y-1) && !maze[x][y-1].isVisited()){
                neigh.add(maze[x][y-1]);
            }
            Collections.shuffle(neigh);
            if (!neigh.isEmpty()){
                Cell newCell = neigh.get(0);
                if (newCell.getX() > x){
                    newCell.updateWalls((byte) 1);
                    maze[x][y].updateWalls((byte) 2);
                } else if (newCell.getX() < x){
                    newCell.updateWalls((byte) 2);
                    maze[x][y].updateWalls((byte) 1);
                } else if (newCell.getY() < y){
                    newCell.updateWalls((byte) 4);
                    maze[x][y].updateWalls((byte) 8);
                } else if (newCell.getY() > y){
                    newCell.updateWalls((byte) 8);
                    maze[x][y].updateWalls((byte) 4);
                }
                newCell.setVisited(true);
                recurseGenerate(newCell.getX(), newCell.getY());
            }
        }
    }

    private boolean isValid(int x, int y){
        return !(x < 0 || x >= X || y < 0 || y >= Y);
    }

    private void initiate(){
        for (int i = 0; i < X; i++){
            for (int j = 0; j < Y; j++){
                maze[i][j] = new Cell(i,j,0,(byte)15);
            }
        }
    }

    public void display(){
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                System.out.print(maze[i][j].getWalls() + " ");
            }
            System.out.println("\n");
        }
    }


    public static void main(String[] args) {
       Maze aMaze = new Maze(4,4);
       aMaze.initiate();
       aMaze.generate();
       aMaze.display();
    }
}