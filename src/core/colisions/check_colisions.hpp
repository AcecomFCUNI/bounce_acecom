#include <vector>
#include<iostream>
#include "../objects/lemur_object.hpp"

static void CheckLemurColisions(std::vector<object_color> bars, lemur_object* lemur){
	if(lemur->GetCenterX() + lemur->GetOffsetX() >= 1 ||lemur->GetCenterX() - lemur->GetOffsetX() <= -1){
		lemur->InverseXVelocity();
	}

	if(lemur->GetCenterY() + lemur->GetOffsetY() >= 1 ||lemur->GetCenterY() - lemur->GetOffsetY() <= -1){
		lemur->InverseYVelocity();
	}

	for(int i = 0; i < bars.size(); i++){
		if(	lemur->GetCenterX() + lemur->GetOffsetX() > bars.at(i).GetCenterX() - bars.at(i).GetOffsetX() &&
			lemur->GetCenterX() - lemur->GetOffsetX() < bars.at(i).GetCenterX() + bars.at(i).GetOffsetX()){

			switch (i) {
			
			case 0: //player 1 (its down)
				
				if(lemur->GetCenterY() - lemur->GetOffsetY() < bars.at(i).GetCenterY() + bars.at(i).GetOffsetY()){
					lemur->InverseYVelocity();
				}

				break;
	
			case 1: //player 2 ( its up)
				
				if(lemur->GetCenterY() + lemur->GetOffsetY() >= bars.at(i).GetCenterY() - bars.at(i).GetOffsetY()){
					lemur->InverseYVelocity();
				}

				break;
	
			default:
				break;
			}
		}
	}
}