I chose for rapidjson as my file reader because of the user friendlyness.
For optimisation of collisions when loading in a level it groups the walls toghether there are some bugs with this.
the event system uses an event queue with observers and a messaging system.
collisions are checked in a for_each loop from stl so i could use execution policys to make the check go faster.
