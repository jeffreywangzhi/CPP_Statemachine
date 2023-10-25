#include <iostream>
#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/deferral.hpp>
namespace sc = boost::statechart;
namespace mpl = boost::mpl;
using namespace std;

// States
struct firstState;
struct secondState;


// Events
struct event_OutOfBlueEvent : sc::event<event_OutOfBlueEvent> {};
struct event_OutOfGreenEvent : sc::event<event_OutOfGreenEvent> {};
struct event_MoveToSecond : sc::event<event_MoveToSecond> {};

struct statemachine : sc::state_machine<statemachine, firstState>{};

struct firstState : sc::simple_state<firstState, statemachine> {
	firstState() { cout << "In State => firstState" << endl; }
	typedef mpl::list<
		sc::deferral<event_OutOfBlueEvent>,
		sc::deferral<event_OutOfGreenEvent>,
		sc::transition<event_MoveToSecond, secondState>
	>reactions;

};

struct secondState : sc::simple_state<secondState, statemachine> {
	secondState() { cout << "In State => secondState" << endl; }
	typedef mpl::list<
		sc::custom_reaction<event_OutOfGreenEvent>,
		sc::custom_reaction<event_OutOfBlueEvent>
		> reactions;
	sc::result react(const event_OutOfBlueEvent & event) {
		cout << "event_OutOfBlueEvent Tiggered in => secondState" << endl;
		return discard_event();
	}
	sc::result react(const event_OutOfGreenEvent & event) {
		cout << "event_OutOfGreenEvent Tiggered in => secondState" << endl;
		return discard_event();
	}
};


int main() {
	statemachine sm;
	sm.initiate();
	// will do nothing
	sm.process_event(event_OutOfBlueEvent());
	// will change state and trigger event_OutOfBlueEvent and event_OutOfGreenEvent in second state
	sm.process_event(event_MoveToSecond());
	return 0;
}

