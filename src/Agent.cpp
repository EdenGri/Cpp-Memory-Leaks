//
// Created by spl211 on 31/10/2020.
//

#include <Agent.h>

Agent::Agent(Session& session): session(session) {

}

ContactTracer::ContactTracer(Session &session) : Agent(session) {

}

Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd) {
}
