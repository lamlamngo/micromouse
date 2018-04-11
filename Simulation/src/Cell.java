public class Cell {
    private int distance;
    private byte walls;
    private boolean visited;

    public Cell(int distance, byte walls){
        this.distance = distance;
        this.walls = walls;
        visited = false;
    }

    public boolean isVisited(){
        return visited;
    }

    public void setVisited(){
        this.visited = true;
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
