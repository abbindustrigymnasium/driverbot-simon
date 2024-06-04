import { writable } from "svelte/store";
import Paho from "paho-mqtt";

// Create a Svelte store to hold the MQTT client
export const clientStore = writable<Paho.Client | null>(null);

export default async function (direction: string) {
  const clientId = "ClientId-" + Math.random() * 1000;
  const brokerIP = "broker.hivemq.com"; // HiveMQ public broker
  const topic = "simon.svoboda@hitachigymnasiet.se/direction";

  // Get the current value of the client store
  let client: Paho.Client | null;
  clientStore.subscribe((value) => {
    client = value;
  })();

  // If the client does not exist, create a new MQTT client
  //@ts-ignore
  if (!client) {
    client = new Paho.Client(`ws://${brokerIP}:8000/mqtt`, clientId);

    // Connect to the broker and publish the direction
    client.connect({
      onSuccess: () => {
        console.log("Connected to the broker");
        const message = new Paho.Message(direction);
        message.destinationName = topic;
        client!.send(message);
      },
    });

    // Update the client store
    clientStore.set(client);
  } else {
    // publish the direction to the topic
    const message = new Paho.Message(direction);
    message.destinationName = topic;
    client!.send(message);
  }
}
