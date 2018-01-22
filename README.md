# Particle Photon - DIY Internet Button
> C code that allows to easily build a Particle Photon based Internet Button

## Prerequisites

- [Particle Photon](https://store.particle.io)
- Two buttons or more, a plastic box, a few electric wires

## How to build the button
<p align="center">
<img src="/images/c_particle_photon_internet_button-parts.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-drilling_button_hole.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-done_drilling.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-done_drilling.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-buttons_in.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-buttons_in.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-buttons_check_alignment.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-preparing_wire.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-preparing_wire.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-tinning.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-soldered.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-fitted.jpg" width="25%"><img src="/images/c_particle_photon_internet_button-button_complete.jpg" width="25%">
</p>

## How to install
* Copy the code contained into c-photon-internet-button.ino into Particle Build: https://build.particle.io/build/new
* Add the required HttpClient library to your project searching it in "Libraries", in your Particle Build project
* Flash it to your Particle Photon
* Cackle into a dark cave

## How to use
I've added two functions for each button: short press and long press.
The long press is activated after keeping the button pressed for 1 second, you can change this value editing longPressTime variable.  Change the sendHttpRequest functions to whatever you want to use your Internet Button for.

## Release History

* 0.0.1
    * Every button has long and short press functions

## Meta

Davide Nastri – [@pitto](https://twitter.com/pitto) – d.nastri@gmail.com

Distributed under the GPL license. See ``LICENSE`` for more information.

[https://github.com/ltpitt/c-photon-internet-button](https://github.com/ltpitt/c-photon-internet-button)

## Contributing

1. Fork it (<https://github.com/ltpitt/c-photon-internet-button/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
