# smartCopertura_sisemb
Sistema di copertura automatico contro grandine e intemperie - Progetto Sistemi Embedded di Antonio Mazzaccaro

Il progetto consiste nella realizzazione di un sistema di copertura in grado di riconoscere e azionarsi a fronte eventi atmosferici avversi intensi (in questo prototipo si tengono conto della grandine e della pioggia di cenere vulcanica), facendo scendere una sorta di "saracinesca" resistente.
In un'epoca in cui i fenomeni meteorologici estremi sono in netto aumento questo sistema troverebbe molto impiego ad esempio nella protezione di pannelli solari, oppure nell'agricoltura (le grandinate forti distruggono tranquillamente le coperture tradizionali delle serre).

![pannelli](./asset/images/pannelli.jpg)

Il riconoscimento di tali fenomeni avversi passa per un'analisi dell'audio ambientale, tramite un microfono, e dalla raccolta in un piccolo recipiente dei chicchi di grandine (o del materiale vulcanico), tramite un sensore di pressione che ne segnala la presenza, mentre la chiusura della "saracinesca" si compie azionando un motore.
Alla fine della grandinata i chicchi presenti nel recipiente (opportunamente bucato, simile a uno scolapasta) vengono scaldati con una resistenza per scioglierli in base alla loro temperatura (feedback closed-loop), mentre, in caso di una pioggia di cenere vulcanica, chiaramente non si possono sciogliere i detriti accumulati: questo sarebbe l'unico caso in cui, nella realtà, si renderebbe necessario l'intervento umano per poter riprendere a funzionare correttamente.
Il sistema acquisisce anche informazioni sul meteo attuale dalla rete, per cercare di ridurre i falsi-positivi e i falsi-negativi, combinando la probabilità di eventi estremi riportata con il grado di confidenza ottenuto dalla valutazione dei suddetti input (suono e peso).

# Hardware
Il prototipo è realizzato con un'ESP32-WROOM32, il quale combina la presenza del modulo WiFi per la connettività e un discreto numero di GPIO (alcuni dei quali dotati anche di DAC e ADC, oltre alla PWM) alle discrete prestazioni dei due core Xtensa a 240MHz. All'MCU sono collegati il microfono per il riconoscimento del suono della grandine, un sensore di pressione, sopra il quale è collocato il cestello che raccoglie i chicchi, un sensore di temperatura (che nell'ambito della demo sarà sostituito da un potenziometro per poter pilotare la temperatura voluta), una resistenza riscaldante (che per ovvi motivi, come per il sensore di temperatura, sarà sostituita da un LED rosso), un ponte H per pilotare il motore che aziona la "saracinesca" e due fine-corsa per fermarne l'apertura e la chiusura.

![prototipo](./asset/images/prototipo.jpg)

Il motore utilizzato nel prototipo è uno step-motor: tale scelta è dovuta principalmente alla precisione maggiore rispetto ad un motore in corrente continua (sia in termini di posizione e sia in termini di regolazione della velocità). Uno svantaggio di tale scelta è che il motore rimane sempre alimentato, anche da fermo.

![motore](./asset/images/motore.jpg)

I fine-corsa usati in questo progetto sono "improvvisati", infatti sono stati realizzati con tre cavetti semi-rigidi, di cui due fissati nei punti di massima apertura e massima chiusura, piegati in modo da fare contatto col cavetto che porta tensione, il quale è fissato sulla cinghia che trasporta la saracinesca.

![fine-corsa](./asset/images/fine-corsa.jpg)