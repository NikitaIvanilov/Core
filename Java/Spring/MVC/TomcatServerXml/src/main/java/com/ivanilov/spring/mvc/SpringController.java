package com.ivanilov.spring.mvc;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class SpringController {

    @GetMapping("/hello-world")
    public String sayHello() {

        return "hello_world";

    }

}
