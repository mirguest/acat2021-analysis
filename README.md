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
* [ ] Do the dummy event mixing without electronics (OECEvent data)
  * The rates (see https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Data_production/mixed):
    * U238 in LS: 3.224 Hz
    * Th232 in LS: 0.792 Hz
    * K40 in LS: 0.518 Hz
* [ ] Generate the index data for further data reduction
