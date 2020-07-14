library(dslabs)
library(tidyverse)
library(gtools)

data("gapminder")

gapminder %>% filter(country %in% c("Cambodia", "Rwanda")) %>% 
  group_by(country) %>% 
  ggplot(aes(x = year, y = population, color = country)) + geom_line() + 
  ggtitle("Population decreases due to genocide") + xlab("year") +
  ylab("population")