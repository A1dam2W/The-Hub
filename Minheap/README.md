My valgrind causes too frequent seg-faults
The key implementations of this program are:
1. Reading from input file and store the data into map, to optimize search runtime.
2. Use Minheap to optimize add and remove runtime.
3. Carry out A-star search.
4. str comparison:
   //                            else if(temp2->priority == openset->priority_at_pos(k)){
   //                                openset->add(temp2, temp2->priority);
   //                                for(int i = 1; i < openset->size; i++){
   //                                    if(openset->item_at_pos(i)->word > openset->peek()->word){
   //                                        swap(openset[0],openset[i]);
   //                                    }
   //                                }
   //                                openset->remove();
   //                            }
