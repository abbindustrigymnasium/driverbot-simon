import { writable } from "svelte/store";
import mqtt from "mqtt";

// Initialize the MQTT client
const client = mqtt.connect("mqtt://your_broker_url");

const mqttClient = writable(client);

// Function to publish a message
const publishMessage = (topic : string, message : string) => {
 client.publish(topic, message, { qos: 0, retain: false }, (err) => {
    if (err) {
      console.error('Error publishing message:', err);
    } else {
      console.log('Message published successfully');
    }
 });
};

export { mqttClient, publishMessage };