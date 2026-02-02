#include <iostream>

class ICarModule {
public:
    virtual void StartEngine() = 0;
    virtual void StopEngine() = 0;
    virtual void TurnOnRadio() = 0;
    virtual void SetFrequency(double freq) = 0;
    virtual void StartNavigation() = 0;
};

class EngineUnit : public ICarModule {
public:
    void StartEngine() override {
        std::cout << "Engine started\n";
    }

    void StopEngine() override {
        std::cout << "Engine stopped\n";
    }

    void TurnOnRadio() override {}
    void SetFrequency(double) override {}
    void StartNavigation() override {}
};

class RadioTuner : public ICarModule {
public:
    void StartEngine() override {}
    void StopEngine() override {}

    void TurnOnRadio() override {
        std::cout << "Radio on\n";
    }

    void SetFrequency(double freq) override {
        std::cout << "Radio frequency set to " << freq << "\n";
    }

    void StartNavigation() override {}
};

class GPSModule : public ICarModule {
public:
    void StartEngine() override {}
    void StopEngine() override {}
    void TurnOnRadio() override {}
    void SetFrequency(double) override {}

    void StartNavigation() override {
        std::cout << "Navigation started\n";
    }
};

class CarComputer {
private:
    EngineUnit engine;
    RadioTuner radio;
    GPSModule gps;

public:
    void StartCar() {
        engine.StartEngine();
    }

    void PlayMusic() {
        radio.TurnOnRadio();
        radio.SetFrequency(101.5);
    }

    void Navigate() {
        gps.StartNavigation();
    }
};

int main() {
    CarComputer car;
    GPSModule GPS;
    car.StartCar();
    car.PlayMusic();
    car.Navigate();
    GPS.StartEngine();
}
