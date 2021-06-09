package packageName.something;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

@Component
@Scope("singleton")
public class MusicPlayer {

    @Autowired
    @Qualifier("rockMusic")
    private Music   music;

    @Value("${musicPlayer.volume}")
    private Integer volume;

    @Value("${musicPlayer.name}")
    private String name;

    public String  getMusic () { return music.getSong(); }
    public Integer getVolume() { return volume;          }
    public String  getName  () { return name;            }

    public void setMusic (Music   music)  { this.music  = music;  }
    public void setVolume(Integer volume) { this.volume = volume; }
    public void setName  (String  name)   { this.name   = name;   }

    @PostConstruct
    private void powerOn () { System.out.println("Power on");  }

    @PreDestroy
    private void powerOff() { System.out.println("Power off"); }

    public void play() {

        System.out.printf(

                "Device: %s\nVolume: %d\nSong: %s\n",

                getName(),
                getVolume(),
                getMusic()

        );

    }

}
