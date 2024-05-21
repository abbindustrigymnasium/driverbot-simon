import { json } from "@sveltejs/kit";
import mqtt from "mqtt";
import { getClientStore, setClientStore } from "$lib/server/clientStore";

type PostRequest = { request: Request; params: { method: string } };

export async function POST({ request, params }: PostRequest) {
  const { topic, message } = await request.json();

  const publisherPrefix = "💻 - Publisher: ";
  let client = getClientStore();

//   Check if the client is already connected
  if (!client) {
    const client = mqtt.connect("mqtt://3.121.8.173:1883", {
      clientId: "publisher",
      clean: false,
        //   @ts-ignore
      will: { topic: "simon.svoboda@hitachigymnasiet.se/offline", payload: "offline", qos: 0 },
    });
    setClientStore(client);
  }

//   Refrash the client
  client = getClientStore();

//   Publish the message
  try {
    client.publish(topic, message, {
        qos: 0,
        retain: false,
      });
      // console.log(publisherPrefix + "Message Sent");

      return json({ message: "Message Sent" }, { status: 200 });
  } catch (e) {
    console.error(publisherPrefix + "Error sending message:", e);
    return json({ message: "Error sending message" }, { status: 500 });
  }
}
