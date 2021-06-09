package packageName.something;

import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

@Component
@Scope("singleton")
public class ClassicMusic extends MusicAbstract {

    public ClassicMusic() {

        setSong("Offenbach - Can Can");

    }
}
