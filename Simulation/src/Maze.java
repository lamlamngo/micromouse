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
}