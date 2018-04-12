public class Cell {
    private int distance;
    private byte walls;
    private boolean visited;
    private int x;
    private int y;

    public Cell(int x, int y, int distance, byte walls){
        this.distance = distance;
        this.walls = walls;
        visited = false;
        this.x = x;
        this.y = y;
    }

    public int getX(){
        return x;
    }

    public int getY(){
        return y;
    }

    public boolean isVisited(){
        return visited;
    }

    public void setVisited(boolean val){
        this.visited = val;
    }

    public void setDistance(int distance){
        this.distance = distance;
    }

    public void setWalls(byte walls){
        this.walls = walls;
    }

    public void updateWalls(byte walls){
        this.walls -= walls;
    }

    public boolean isWall(byte direction){
        return ((byte) (this.walls & direction) == 0);
    }

    public byte getWalls(){
        return walls;
    }

    public int getDistance(){
        return distance;
    }
}
