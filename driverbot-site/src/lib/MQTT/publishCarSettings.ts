import { writable } from "svelte/store";
import Paho from "paho-mqtt";

// Create a writable Svelte store to hold the MQTT client
export const clientStore = writable<Paho.Client | null>(null);

export default async function (component: string, value: number) {
  // Generate a random client ID
  const clientId = "ClientId-" + Math.random() * 1000;
  const brokerIP = "broker.hivemq.com";
  const topic = `simon.svoboda@hitachigymnasiet.se/${component}`;

  // Subscribe to the client store to get the current MQTT client
  let client: Paho.Client | null;
  clientStore.subscribe((value) => {
    client = value;
  })();

  // If the client doesn't exist, create a new one and connect to the broker
  //@ts-ignore
  if (!client) {
    client = new Paho.Client(`ws://${brokerIP}:8000/mqtt`, clientId);

    // Connect to the broker and send a message with the given value
    client.connect({
      onSuccess: () => {
        console.log("Connected to the broker");
        const message = new Paho.Message(value.toString());
        message.destinationName = topic;
        client!.send(message);
      },
    });

    // Update the client store with the new client
    clientStore.set(client);
  }
}