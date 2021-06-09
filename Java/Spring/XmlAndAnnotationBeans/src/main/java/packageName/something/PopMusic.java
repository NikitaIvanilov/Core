package packageName.something;

import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Component;

@Component
@Scope("singleton")
public class PopMusic extends MusicAbstract {

    public PopMusic() {

        setSong("Billie Eilish - bad guy");

    }
}
