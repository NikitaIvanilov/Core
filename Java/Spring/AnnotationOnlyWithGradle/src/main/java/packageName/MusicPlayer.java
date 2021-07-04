package packageName;

public class MusicPlayer {

    private Music   music;
    private Integer volume;
    private String  name;

    public String  getMusic () { return music.getSong(); }
    public Integer getVolume() { return volume;          }
    public String  getName  () { return name;            }

    public void setMusic (Music   music)  { this.music  = music;  }
    public void setVolume(Integer volume) { this.volume = volume; }
    public void setName  (String  name)   { this.name   = name;   }

    private void powerOn () { System.out.println("Power on");  }
    private void powerOff() { System.out.println("Power off"); }

    public MusicPlayer(Music music, Integer volume, String name) {

        setMusic (music);
        setVolume(volume);
        setName  (name);

    }

    public void play() {

        System.out.printf(

                "Device: %s\nVolume: %d\nSong: %s\n",

                getName(),
                getVolume(),
                getMusic()

        );

    }

}