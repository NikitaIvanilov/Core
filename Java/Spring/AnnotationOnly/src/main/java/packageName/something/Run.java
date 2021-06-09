package packageName.something;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Run {

    public static void main(String... args) {

        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(

                SpringConfig.class

        );

        MusicPlayer musicPlayer = context.getBean("musicPlayer", MusicPlayer.class);

        musicPlayer.play();
        context.close();

    }

}
