public class Maze{
    private int x;
    private int y;
    private Cell[][] maze;
    private int[] orientation = {1,2,4,8}; //backward: 1 forward: 2 right: 4 left: 8

    public Maze(int x, int y){
        this.x = x;
        this.y = y;
        maze = new Cell[x][y];
    }

    public void generate(){

    }

    private void initiate(){
        for (int i = 0; i < x; i++){
            for (int j = 0; j < y; j++){
                maze[i][j].setWalls((byte)15);
            }
        }
    }
}