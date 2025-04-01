# Philosophers

This project is part of the 42 curriculum and aims to teach the basics of threading a process. In this project, I created threads and discover mutexes.

## Introduction

The Philosophers project is a classic synchronization problem involving philosophers who are thinking and eating at a table with forks. The goal is to avoid deadlock and ensure that each philosopher can eventually eat.

## Usage

To run the philosophers program, execute the following command:

`$ ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]`

# Real-World Applications and Industry Relevance

The Philosophers project isn't just an academic exercise—it mirrors concurrency and synchronization challenges encountered in real-world systems. Below are key applications of the concepts learned.

---

### Databases (Deadlock Prevention)
Concepts like mutexes and careful resource acquisition (e.g., fork pickup order) are akin to deadlock avoidance in databases. Systems like MySQL, PostgreSQL, and MariaDB use techniques such as Two-Phase Locking (2PL) to manage concurrent transactions.
Relevant Sectors: Tech, Finance.

### Networking (Resource Allocation)
TCP congestion control and fair queuing algorithms ensure efficient packet transmission, similar to ensuring philosophers eat fairly. These principles underpin reliable network communication.
Relevant Sectors: Telecom, Cloud Services.

### High-Performance Systems (Thread Synchronization)
Game engines (e.g., Unreal Engine), web servers (e.g., Nginx), and real-time systems (e.g., automotive software) depend on thread synchronization to prevent race conditions and deadlocks.
Relevant Sectors: Gaming, Automotive, Web Infrastructure.

### Cloud Computing (Resource Scheduling)
Platforms like AWS, Azure, and Kubernetes allocate CPU, RAM, and disk resources among users, avoiding starvation and deadlocks—much like managing philosophers' access to forks.
Relevant Sectors: Cloud Providers, DevOps.

### Cybersecurity (DoS Mitigation)
Deadlocks can be weaponized in denial-of-service (DoS) attacks to exhaust system resources. Understanding synchronization helps design resilient systems.
Relevant Sectors: Cybersecurity, Defense.

### Containerized Environments (Starvation Prevention)
Tools like Docker and Kubernetes use scheduling logic to prevent resource starvation, mirroring the fairness required in the Philosophers problem.
Relevant Sectors: Tech Startups, Enterprise IT.

### Multi-Threaded Programming (Language Ecosystems)
The Dining Philosophers problem is a foundational example for concurrency in languages like Java, C++, and Python, widely used across software development.
Relevant Sectors: Software Engineering, Embedded Systems.

Why Companies Care
Mastering these concepts demonstrates skills critical to industries like cybersecurity, system programming, cloud infrastructure, and software engineering. Companies such as Google, Amazon, Tesla, and CrowdStrike need engineers who can build scalable, efficient and secure systems—skills directly tied to solving problems like the one in this project.

