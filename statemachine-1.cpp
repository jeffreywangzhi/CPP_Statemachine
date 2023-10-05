#include <iostream>
#include <boost/statechart/event.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/transition.hpp>
#include <boost/statechart/custom_reaction.hpp>
namespace sc = boost::statechart;
using namespace std;

struct firstState;
struct secondState;
struct statemachine : sc::state_machine<statemachine, secondState>
{
	statemachine() { cout << "Starting => statemachine" << endl; }
};

struct firstState : sc::simple_state<firstState, statemachine>
{
	firstState() { cout << "In State => firstState" << endl; }
};
struct secondState : sc::simple_state<secondState, statemachine>
{
	secondState() { cout << "In State => secondState" << endl; }
};

int main() {
	statemachine sm;
	sm.initiate();
	return 0;
}
