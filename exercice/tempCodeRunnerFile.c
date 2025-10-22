  while (tmp != NULL)
   {
      empiler_pile(mapile, tmp->valeur);
      depiler_pile(tmp);
   }