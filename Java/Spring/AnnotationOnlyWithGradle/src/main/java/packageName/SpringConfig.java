package packageName;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.PropertySource;

@Configuration
@PropertySource("classpath:musicPlayer.properties")
public class SpringConfig {

    @Value("${musicPlayer.volume}")
    private Integer volume;

    @Value("${musicPlayer.name}")
    private String name;

    @Bean public ClassicMusic classicMusic() { return new ClassicMusic(); }
    @Bean public RockMusic    rockMusic   () { return new RockMusic   (); } // <--
    @Bean public PopMusic     popMusic    () { return new PopMusic    (); }

    @Bean public MusicPlayer  musicPlayer () { return new MusicPlayer(popMusic(), volume, name); }

}
