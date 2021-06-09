package packageName.something;

public abstract class MusicAbstract implements Music {

    String song;

    public String getSong(){

        return song;

    }

    protected void setSong(String song){

        this.song = song;

    }

}
