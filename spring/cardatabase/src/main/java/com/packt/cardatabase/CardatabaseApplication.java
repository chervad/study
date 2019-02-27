package com.packt.cardatabase;

import com.packt.cardatabase.domain.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class CardatabaseApplication {

	private final static Logger logger = LoggerFactory.getLogger(CardatabaseApplication.class);

	@Autowired
	private CarRepository carRepository;

	@Autowired
	private OwnerRepository ownerRepository;

	@Autowired
	private UserRepository userRepository;

	public static void main(String[] args) {
		logger.info("Java version: " + System.getProperty("java.version"));
		SpringApplication.run(CardatabaseApplication.class, args);
	}

	@Bean
	CommandLineRunner runner() {
		return args -> {
			Owner owner0 = new Owner("John", "Johnson");
			Owner owner1 = new Owner("Mary", "Robinson");

			ownerRepository.save(owner0);
			ownerRepository.save(owner1);

			carRepository.save(new Car("Ford", "Mustang", "Red", "ADF-1211", 2017, 59000, owner0));
			carRepository.save(new Car("Nissan", "Leaf", "White", "SSJ-3002", 2014, 29000, owner1));
			carRepository.save(new Car("Toyota", "Prius", "Silver", "KKO-0212", 2018, 39000, owner1));

			userRepository.save(new User("user", "$2a$04$3BLS.vo78qRv9OuePgwwYewv4yrqzGP5U8KxQntp/Dl4VCaJMkeAK", "USER"));
			userRepository.save(new User("admin", "$2a$04$yQFwfEe.vVC.wLPMrOqStuI3WbI6S4hZrMwUDvMz8Av4v/wuBgGzC", "ADMIN"));
		};
	}
}

