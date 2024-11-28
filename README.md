# A1 Mediator for FlexRIC

## Run A1 Mediator
```
cd A1_Mediator
pip3 install -r requirements.txt
cd app
python3 main.py
type in browser: (host_ip):9000/docs #to see available APIs
```

## Run test xApp with FlexRIC
```
use local FlexRIC build
build FlexRIC following repo instructions
run RIC with: 
./flexric-a1-xapp-A1_integration_RIC_TaaP/build/examples/ric/nearRT-RIC
run ns3 with nearRT-RIC connection
run xApp:
./flexric-a1-xapp-A1_integration_RIC_TaaP/build/examples/xApp/c/kpm_rc_A1/xapp_kpm_rc_a1
```

## Supported API calls
| **Method** | **Endpoint**                                                | **Description**                |
|------------|-------------------------------------------------------------|--------------------------------|
| GET        | /a1-p/policytypes                                           | Get All Policy Types          |
| GET        | /a1-p/policytypes/{policy_type_id}                          | Get Policy Type               |
| PUT        | /a1-p/policytypes/{policy_type_id}                          | Create Policy Type            |
| DELETE     | /a1-p/policytypes/{policy_type_id}                          | Delete Policy Type            |
| PUT        | /a1-p/policytypes/{policy_type_id}/policies/{policy_instance_id} | Create Policy Instance        |
| DELETE     | /a1-p/policytypes/{policy_type_id}/policies/{policy_instance_id} | Delete Policy Instance        |
| GET        | /a1-p/policytypes/{policy_type_id}/policies/{policy_instance_id}/status | Get Policy Instance Status    |
| GET        | /a1-p/policytypes/{policy_type_id}/policies                 | List Policy Instances         |



## Contributers
- Jerzy Jegier, Orange Innovation Poland, jerzy.jegier@orange.com
- [Kamil Kociszewski](https://www.linkedin.com/in/kociszz/), Orange Innovation Poland, kamil.kociszewski@orange.com