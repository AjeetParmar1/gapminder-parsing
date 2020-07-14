library(dslabs)
library(tidyverse)
library(gtools)

data("gapminder")

west <- c("Western Europe", "Northern Europe", "Southern Europe", "Northern America", "Australia and New Zealand")
transitional <- c("Russia", "India", "Brazil", "China", "South Africa")

gapminder %>% filter(year == 2010) %>%
  mutate(group = ifelse(region %in% west, "West", ifelse(country %in% transitional, "transitional", "Developing"))) %>%
  ggplot(aes(y = gdp/population, x = group, color = group)) +
  geom_boxplot()  
