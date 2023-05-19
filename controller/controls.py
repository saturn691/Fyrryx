import inputs

def get_button_events():
    events = inputs.get_gamepad()
    for event in events:
        if event.ev_type == "button" and "ABS_" not in event.code:
            if event.code == "BTN_Y" and event.state == 1:
                return "Y"
            elif event.code == "BTN_RT" and event.state == 1:
                return "RT"
            elif event.code == "BTN_RB" and event.state == 1:
                return "RB"
            elif event.code == "BTN_LT" and event.state == 1:
                return "LT"
            elif event.code == "BTN_LB" and event.state == 1:
                return "LB"
            elif event.code == "BTN_A" and event.state == 1:
                return "A"
            elif event.code == "BTN_B" and event.state == 1:
                return "B"
            elif event.code == "BTN_X" and event.state == 1:
                return "X"
            elif event.code == "BTN_UP" and event.state == 1:
                return "Up"
            elif event.code == "BTN_DOWN" and event.state == 1:
                return "Down"
            # Add more button conditions as needed