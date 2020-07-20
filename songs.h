/*-- Fur Elise --*/
void note(int frequencyInHertz, int noteLength)  //Code to take care of the note
{
  tone(buzPin, frequencyInHertz);
  float delayTime = (1000/tempo) * (60/4) * noteLength;
  delay(delayTime);
}

void FurElise() {
  //Measure 1
  note(NOTE_E6, EIGHTHNOTE);
  note(NOTE_DS6, EIGHTHNOTE);
  
  //Measure 2
  note(NOTE_E6, EIGHTHNOTE);
  note(NOTE_DS6, EIGHTHNOTE);
  note(NOTE_E6, EIGHTHNOTE);
  note(NOTE_B5, EIGHTHNOTE);
  note(NOTE_D6, EIGHTHNOTE);
  note(NOTE_C6, EIGHTHNOTE);
  
  //Measure 3
  note(NOTE_A3, EIGHTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(NOTE_A4, EIGHTHNOTE);
  note(NOTE_C5, EIGHTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(NOTE_A5, EIGHTHNOTE);
  
  //Measure 4
  note(NOTE_E3, EIGHTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(NOTE_GS4, EIGHTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(NOTE_GS5, EIGHTHNOTE);
  note(NOTE_B5, EIGHTHNOTE);
  
  //Measure 5
  note(NOTE_A3, EIGHTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(NOTE_A4, EIGHTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(NOTE_E6, EIGHTHNOTE);
  note(NOTE_DS6, EIGHTHNOTE);
  
  //Measure 6
  note(NOTE_E6, EIGHTHNOTE);
  note(NOTE_DS6, EIGHTHNOTE);
  note(NOTE_E6, EIGHTHNOTE);
  note(NOTE_B5, EIGHTHNOTE);
  note(NOTE_D6, EIGHTHNOTE);
  note(NOTE_C6, EIGHTHNOTE);
  
  //Measure 7
  note(NOTE_A3, EIGHTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(NOTE_A4, EIGHTHNOTE);
  note(NOTE_C5, EIGHTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(NOTE_A5, EIGHTHNOTE);
  
  //Measure 8
  note(NOTE_E3, EIGHTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(NOTE_GS4, EIGHTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(NOTE_GS5, EIGHTHNOTE);
  note(NOTE_B5, EIGHTHNOTE);
  
  //Measure 9
  note(NOTE_A3, EIGHTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(NOTE_A4, EIGHTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(NOTE_C6, EIGHTHNOTE);
  note(NOTE_D6, EIGHTHNOTE);
  
  //Measure 10
  note(NOTE_C4, EIGHTHNOTE);
  note(NOTE_G4, EIGHTHNOTE);
  note(NOTE_C5, EIGHTHNOTE);
  note(NOTE_G5, EIGHTHNOTE);
  note(NOTE_F6, EIGHTHNOTE);
  note(NOTE_E6, EIGHTHNOTE);
  
  //Measure 11
  note(NOTE_G3, EIGHTHNOTE);
  note(NOTE_G4, EIGHTHNOTE);
  note(NOTE_B4, EIGHTHNOTE);
  note(NOTE_F5, EIGHTHNOTE);
  note(NOTE_E6, EIGHTHNOTE);
  note(NOTE_D6, EIGHTHNOTE);
  
  //Measure 12
  note(NOTE_A3, EIGHTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(NOTE_A4, EIGHTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(NOTE_D6, EIGHTHNOTE);
  note(NOTE_C6, EIGHTHNOTE);
  
  //Measure 13
  note(NOTE_E3, EIGHTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(NOTE_A5, EIGHTHNOTE);
  noTone(buzPin);
}

void MarioMain() {
    note(NOTE_E5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_C5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  
  note(NOTE_E5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_G5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_G4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_C5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
 
  note(NOTE_G4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_E4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_A4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_B4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
 
  note(NOTE_AS4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_A4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_G4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_E5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  
  note(NOTE_G5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_A5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_F5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_G5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  
  note(NOTE_E5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_C5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_D5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_B4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);

  note(NOTE_C5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_G4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_E4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_A4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);

  note(NOTE_B4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_AS4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_A4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_G4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);

  note(NOTE_E5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_G5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_A5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_F5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);

  note(NOTE_G5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_E5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE); 
  note(NOTE_C5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);
  note(NOTE_D5, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);

  note(NOTE_B4, EIGHTHNOTE);
  note(0, SIXTEENTHNOTE);


  noTone(buzPin);   
}
