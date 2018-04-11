public class Cell {
    private int distance;
    private byte walls;

    public Cell(int distance, byte walls){
        this.distance = distance;
        this.walls = walls;
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
