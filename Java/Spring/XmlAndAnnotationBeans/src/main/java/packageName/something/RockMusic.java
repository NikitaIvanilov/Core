package packageName.something;

import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

@Component
@Scope("singleton")
public class RockMusic extends MusicAbstract {

    public RockMusic() {

        setSong("Creedence Clearwater Revival - Run Through The Jungle");

    }

}
