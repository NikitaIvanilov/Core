package packageName.something;

import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Run {

    public static void main(String... args) {

        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext(

                "applicationContext.xml"

        );

        MusicPlayer musicPlayer = context.getBean("musicPlayer", MusicPlayer.class);

        musicPlayer.play();
        context.close();

    }

}
