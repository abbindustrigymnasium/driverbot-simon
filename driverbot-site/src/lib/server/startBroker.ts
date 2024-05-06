import aedes from "aedes";
import { createServer } from "net";
import chalk from "chalk";

export default async function () {
  const brokerPrefix = "💿 Broker: ";
  try {
    console.log(brokerPrefix + "Starting broker");

    // Create an MQTT broker on port 1833
    const broker: aedes = new aedes();
    const server = createServer(broker.handle);
    const port = 1883;

    // Log when a publisher sends a message
    broker.on("publish", (packet) => {
      const heartbeatPattern = /\$SYS\/[a-f0-9-]+/;

      // Ignore all heartbeat topic messages using regex
      if (!heartbeatPattern.test(packet.topic)) {
        console.log(
          `${brokerPrefix}Publisher sent a message: ${chalk.green(
            packet.payload.toString()
          )} on topic ${chalk.blue(packet.topic)}`
        );
      }
    });

    server.listen(port, () => {
      console.log(`MQTT Broker running on port ${port}`);
    });

    return { apiStatus: 200, server: server };
  } catch (e) {
    console.error(brokerPrefix + "Failed to start broker", e);
    return { apiStatus: 500, server: null };
  }
}
