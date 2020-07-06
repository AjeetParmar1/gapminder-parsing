library(dslabs)
library(tidyverse)
library(gtools)

data("gapminder")

#head(gapminder)

gapminder %>% filter(year == 2010) %>% group_by(continent) %>% 
  ggplot(aes(x = continent, y = population, color = continent)) + 
  geom_boxplot() + scale_y_continuous(trans = "log10") + 
  ggtitle("populations per continent in 2010")