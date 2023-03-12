// Your First C++ Program

#include <iostream>
#include <vector>

class Dog {
    public:
        Dog(std::string name): name_(name) {
            std::cout << "making " << name << std::endl;
        }
        Dog(Dog&& dog) {
            std::cout << "moving " << dog.name() << std::endl;
            name_ = std::move(dog.name_);
        }
        Dog(const Dog& dog) {
            std::cout << "copying " << dog.name() << std::endl;
            name_ = dog.name_;
        }
        Dog& operator=(const Dog& other) {
            std::cout << "copy assigning " << other.name() << std::endl;
            name_ = other.name_;
            return *this;
        }
        Dog& operator=(Dog&& other) {
            std::cout << "move assigning " << other.name() << std::endl;
            name_ = other.name_;
            return *this;
        }

        ~Dog() {
            std::cout << name() << " dying" << std::endl;
        }
        const std::string& name() const {
            return name_;
        }

        std::string name_;
};

class Person {
    public:
        Person(Dog&& dog): dog_(std::move(dog)) {}
        ~Person() {
            std::cout << "person dying" << std::endl;
        }
        const std::string& dogName() const {
            return dog_.name();
        }
        Dog dog_;
};

Person giveDogToPersonByRValueRef(Dog&& dog) {
    std::cout << "in giving dog to person" << std::endl;
    return Person{std::move(dog)};
}

void R() {
    Dog{"dog"};
    std::cout << "function ending" << std::endl;
}

void giveRValueAName() {
    Dog dog{"dog"};
    std::cout << "function ending" << std::endl;
}

void LOnTheLeftSide() {
    Dog dog{"dog"}; //L to R
    Dog dog1 = dog; //L to L
    Dog& dogRef = dog;
    Dog dog2 = dogRef; // L to LRef
    Dog dog3 = std::move(dog); // L to RRef
    Dog dog4 = Dog{"dog4"};
    std::cout << "function ending" << std::endl;
}

void LRefOnTheLeftSide() {
    Dog dog{"dog1"};
    Dog& dogRef1 = dog; //LRef to L
    const Dog& dogRef2 = Dog{"dog2"}; //const LRef to R
    Dog& dogRef3 = dogRef1; //LRef to LRef
    dogRef1 = Dog{"dog3"};
    dogRef3 = dogRef2;
    dogRef1 = Dog{"dog4"}; 
    dogRef1 = Dog{"dog5"}; 
    dogRef1 = Dog{"dog6"}; 
    dogRef1 = Dog{"dog7"}; 
    dogRef1 = dogRef3;
    std::cout << "function ending" << std::endl;
} 

void RRefOnTheLeftSide() {
    Dog&& dog{"dog"};
    dog = Dog{"dog2"};
    Dog&& dogRRef2 = std::move(dog);
    Dog&& dogRRef3 = std::move(dog);
    dogRRef2 = std::move(dogRRef3);
    Dog& dogLRef = dogRRef3;
    dogRRef3 = std::move(dogLRef);

    dog = std::move(dogRRef2);
    std::cout << "function ending" << std::endl;
}



int main() {
    R();
    std::cout << "-------------" << std::endl;
    giveRValueAName();
    std::cout << "-------------" << std::endl;
    LOnTheLeftSide();
    std::cout << "-------------" << std::endl;
    LRefOnTheLeftSide();
    std::cout << "-------------" << std::endl;
    RRefOnTheLeftSide();
    std::cout << "-------------" << std::endl;
    return 0;
}



