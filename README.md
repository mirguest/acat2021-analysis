# JUNO Offline Analysis Example (ACAT 2021)

* See https://indico.cern.ch/event/855454/contributions/4605040/
* Authors:
  * Weidong Li
  * Tao Lin
  * Yan Liu
  * Yixiang Yang
  * Jiaheng Zou

## Quickstart

```bash
$ git clone git@github.com:mirguest/acat2021-analysis.git
$ cd offline-example-pyalg
$ source  /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/latest/setup.sh
$ ./build.sh
$ source InstallArea/setup.sh
```

## Generation OECEvent for analysis

* [x] Generate radioactivity backgrounds using detector simulation software (SimEvent data)
  * U238, Th232, K40 etc. 
  * In this example, we reuse the existing datasets under
    * `/junofs/production/data-production/Pre-Releases/J20v1r0-Pre2/background/LS/`
* [x] Do the dummy event mixing without electronics (OECEvent data)
  * The rates (see https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Data_production/mixed):
    * U238 in LS: 3.224 Hz
    * Th232 in LS: 0.792 Hz
    * K40 in LS: 0.518 Hz
* [ ] Generate the index data for further data reduction
  * IBD Selection:
    * Ep: [0.7MeV, 12MeV]
    * Ed: [1.9MeV, 2.5MeV]
    * Tp-d: < 1.0ms
    * Dp-d: < 1.5m
  * Loose selection (From Jie Zhao's talk):
    * Ep: [0.5MeV, 12MeV]
    * Ed: [1.0MeV, 12MeV]
    * Tp-d: < 2.5ms
    * Dp-d: < 4.0m

```bash

$ python DummyEventMixing/share/run.py --evtmax 1000000 --output sample_oec_1M.root

$ python DummyEventSelection/share/run.py --evtmax -1 --input sample_oec_1M.root --delay-energy-min 1 --delay-energy-max 12 --prompt-energy-min 0.5 --prompt-energy-max 12 --time-cut 0.0025 --dist-cut 4
junotoptask:SelectionAlg.finalize  INFO: Total process 1000000 events.
junotoptask:SelectionAlg.finalize  INFO: Total select 10 events.
junotoptask:SelectionAlg.finalize  INFO: Total select (cutn) 999894 events. 99.9894%
junotoptask:SelectionAlg.finalize  INFO: Total select (energy delay) 194621 events. 19.4621%
junotoptask:SelectionAlg.finalize  INFO: Total select (energy prompt) 178731 events. 17.8731%
junotoptask:SelectionAlg.finalize  INFO: Total select (delta time) 1225 events. 0.1225%
junotoptask:SelectionAlg.finalize  INFO: Total select (prompt) 10 events. 0.001%
junotoptask:SelectionAlg.finalize  INFO:  Using Following cuts:
junotoptask:SelectionAlg.finalize  INFO:  Delay Energy Range: [1, 12]
junotoptask:SelectionAlg.finalize  INFO:  Prompt Energy Range: [0.5, 12]
junotoptask:SelectionAlg.finalize  INFO:  Delta time cut (s): 0.0025
junotoptask:SelectionAlg.finalize  INFO:  Distance cut (m): 4
```
