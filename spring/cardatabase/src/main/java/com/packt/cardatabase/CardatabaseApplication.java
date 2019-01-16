package com.packt.cardatabase;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import com.packt.cardatabase.domain.Car;
import com.packt.cardatabase.domain.CarRepository;
import org.springframework.context.annotation.Bean;

@SpringBootApplication
public class CardatabaseApplication {

	private final static Logger logger = LoggerFactory.getLogger(CardatabaseApplication.class);

	@Autowired
	private CarRepository repository;

	public static void main(String[] args) {
		SpringApplication.run(CardatabaseApplication.class, args);
		logger.info("Hello world!");
	}

	@Bean
	CommandLineRunner runner() {
		return args -> {
			repository.save(new Car("Ford", "Mustang", "Red", "ADF-1211", 2017, 59000));
			repository.save(new Car("Nissan", "Leaf", "White", "SSJ-3002", 2014, 29000));
			repository.save(new Car("Toyota", "Prius", "Silver", "KKO-0212", 2018, 39000));
		};
	}
}

