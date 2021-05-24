package packageName.something;

public class MusicPlayer {

    Music music;
/*
    MusicPlayer(Music music) {

        this.music = music;

    }
*/
    public void setMusic(Music music) {

        this.music = music;

    }

    public void run() {

        music.run();

    }

}
