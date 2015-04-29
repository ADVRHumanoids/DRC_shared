#ifndef DRAW_STATE_MACHINE_HPP
#define DRAW_STATE_MACHINE_HPP

#include <map>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <cxxabi.h>

struct stat;
namespace walkman{
    namespace drc{

        template <class state_type, class transition_type>
        class draw_state_machine
        {
            std::vector<int> nodes;
            std::map<int,std::pair<int,int>> arcs;
            std::map<int,state_type> states_ids;
            std::map<int,transition_type> arcs_ids;
            std::map<int, std::pair<int,int>>coords;
        public:
            draw_state_machine()
            {
            }
            std::map<state_type,std::map<transition_type,state_type>> transition_table;
            void insert(std::vector< std::tuple< state_type, transition_type, state_type > > table)
            {
                for (auto row:table)
                    insert(row);
            }
            
            void insert(std::tuple< state_type, transition_type, state_type > row)
            {
                transition_table[std::get<0>(row)][std::get<1>(row)]=std::get<2>(row);
            }
        private:
            void calculateForces(double& xvel,double& yvel, int nsource)
            {
                xvel = 0;
                yvel = 0;
                // Sum up all forces pushing this item away
                for (auto ntarget:nodes) //for all the sources
                {
                    double dx = coords[nsource].first-coords[ntarget].first;
                    double dy = coords[nsource].second-coords[ntarget].second;
                    double l = 2.0 * (dx * dx + dy * dy);
                    if (l > 0) {
                        xvel += (dx * 150.0) / l;
                        yvel += (dy * 150.0) / l;
                    }
                }
                // Now subtract all forces pulling items together
                double weight = (arcs.size()+1) * 10;
                for (auto a:arcs)
                {
                    if (a.second.first!=nsource) continue;
                    auto delta_0=coords[a.second.second].first-coords[nsource].first;
                    auto delta_1=coords[a.second.second].second-coords[nsource].second;
                    xvel -= delta_0 / weight;
                    yvel -= delta_1 / weight;
                }
                for (auto a:arcs)
                {
                    if (a.second.second!=nsource) continue;
                    auto delta_0=coords[a.second.first].first-coords[nsource].first;
                    auto delta_1=coords[a.second.first].second-coords[nsource].first;
                    xvel -= delta_0 / weight;
                    yvel -= delta_1 / weight;
                }
                if (abs(xvel) < 0.1)
                    xvel=0;
                if (abs(yvel) < 0.1)
                    yvel = 0;
            }

            std::string convert_to_string(state_type state)
            {
                // unmangled
                int status = 0;
                char* demangled = abi::__cxa_demangle(typeid(state).name(), 0, 0, &status);
                
                switch (status) {
                    case -1: {
                        // could not allocate memory
                        std::cout << "Could not allocate memory" << std::endl;
                        return "";
                    } break;
                    case -2: {
                        // invalid name under the C++ ABI mangling rules
                        std::cout << "Invalid name" << std::endl;
                        return "";
                    } break;
                    case -3: {
                        // invalid argument
                        std::cout << "Invalid argument to demangle()" << std::endl;
                        return "";
                    } break;
                }
                std::string result(demangled);
                
                free(demangled);
                return result;
            }
        public:
            void draw_on_file(std::string filename,std::map<state_type,transition_type> state_map)
            {
               int x=0;
               int y=0;
                for ( auto state:transition_table )
                {
                    x++;
                    nodes.push_back(x);
//                     lemon::SmartDigraph::Node n = graph.addNode();
                    states_ids[x] = state.first;
                    coords[x].first=rand()%100-50;
                    coords[x].second=rand()%100-50;
                }
                for (auto nsource:nodes)
//                 for (auto node: lemon::SmartDigraph::NodeIt nsource(graph); nsource!=lemon::INVALID; ++nsource) //for all the sources
                {
                    for (auto ntarget:nodes)
//                     for (lemon::SmartDigraph::NodeIt ntarget(graph); ntarget!=lemon::INVALID; ++ntarget) //for all the targets
                    {
                        for (auto transition:transition_table[states_ids[nsource]])
                        {
                            if (transition.second==states_ids[ntarget])
                            {
//                                 lemon::SmartDigraph::Arc a=graph.addArc ( nsource,ntarget );
                                y++;
                                arcs[y]=std::make_pair(nsource,ntarget);
                                arcs_ids[y]=transition.first;
                            }
                        }
                    }
                }

                //repulsive approach
                for (int i=0;i<0;i++)
                {
                    double xvel=0;
                    double yvel=0;
                    for (auto nsource:nodes) //for all the sources
                    {
                        calculateForces(xvel,yvel,nsource);
                        coords[nsource].first+=xvel;
                        coords[nsource].second+=yvel;
                        if (coords[nsource].first>50) coords[nsource].first=50;
                        if (coords[nsource].first<-50) coords[nsource].first=-50;
                        if (coords[nsource].second>50) coords[nsource].second=50;
                        if (coords[nsource].second<-50) coords[nsource].second=-50;
                    }
                }
                std::string final_string;
                std::ostringstream ss;
                /*
                 *               graph [
                 *               comment "This is a sample graph"
                 *               directed 1
                 *               id 42
                 *               label "Hello, I am a graph"
                 *               node [
                 *               id 1
                 *               label "node 1"
                 *               thisIsASampleAttribute 42
                 *               ]
                 *               node [
                 *               id 2
                 *               label "node 2"
                 *               thisIsASampleAttribute 43
                 *               ]
                 *               node [
                 *               id 3
                 *               label "node 3"
                 *               thisIsASampleAttribute 44
                 *               ]
                 *               edge [
                 *               source 1
                 *               target 2
                 *               label "Edge from node 1 to node 2"
                 *               ]
                 *               edge [
                 *               source 2
                 *               target 3
                 *               label "Edge from node 2 to node 3"
                 *               ]
                 *               edge [
                 *               source 3
                 *               target 1
                 *               label "Edge from node 3 to node 1"
                 *               ]
                 *               ]*/
                ss<<"graph ["<<std::endl<<"directed 1"<<std::endl<<"id 42"<<std::endl<<"label \"State machine graph\""<<std::endl;
                for (auto node:nodes)
                    ss<<"node ["<<std::endl<<"id "<<node<<std::endl<<"label \""<<state_map[states_ids[node]] <<"\""<<std::endl<<"]"<<std::endl;
                for (auto edge:arcs)
                    ss<<"edge ["<<std::endl<<"source "<<edge.second.first<<std::endl<<"target "<< edge.second.second <<std::endl<<"]"<<std::endl;
                ss<<"]"<<std::endl;
                std::cout<<ss.str()<<std::endl;
                std::ofstream myfile;
                myfile.open (filename);
                myfile << ss.str();
                myfile.close();
            }
        };

    }
}
#endif // DRAW_STATE_MACHINE_HPP
