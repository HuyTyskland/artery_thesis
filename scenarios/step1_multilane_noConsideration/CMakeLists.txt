add_artery_feature(step1 LLService.cc PLService.cc MService.cc NPService.cc)
generate_opp_message(V2Vmsg.msg TARGET step1 DIRECTORY step1_msgs)
add_opp_run(step1_multilane_noConsideration CONFIG omnetpp.ini)