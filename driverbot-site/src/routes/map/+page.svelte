<script lang="ts">
  import { onMount } from "svelte";
  import { recordInputStore } from "$lib/stores/recordInputStore";

  type point = {
    x: number;
    y: number;
  };

  let svgElement: SVGSVGElement;

  // Function to draw a straight line between two points
  function drawStraightLine(point1: point, point2: point) {
    const svgns = "http://www.w3.org/2000/svg";
    const line = document.createElementNS(svgns, "line");
    line.setAttribute("x1", point1.x.toString());
    line.setAttribute("y1", point1.y.toString());
    line.setAttribute("x2", point2.x.toString());
    line.setAttribute("y2", point2.y.toString());
    line.setAttribute("stroke", "black");
    line.setAttribute("stroke-width", "2");
    svgElement.appendChild(line);
  }

  // Function to draw a curved line between two points with a control point
  function drawCurvedLine(point1: point, point2: point, controlPoint: point) {
    const svgns = "http://www.w3.org/2000/svg";
    const path = document.createElementNS(svgns, "path");

    const pathData = `M ${point1.x} ${point1.y} Q ${controlPoint.x} ${controlPoint.y}, ${point2.x} ${point2.y}`;

    path.setAttribute("d", pathData);
    path.setAttribute("stroke", "black");
    path.setAttribute("stroke-width", "2");
    path.setAttribute("fill", "none");
    svgElement.appendChild(path);
  }

  // Function to draw an arc between two points with a given radius
  function drawArc(startPoint: point, endPoint: point, radius: number) {
    const svgns = "http://www.w3.org/2000/svg";
    const path = document.createElementNS(svgns, "path");

    const pathData = `M ${startPoint.x} ${startPoint.y} A ${radius} ${radius} 0 0 1 ${endPoint.x} ${endPoint.y}`;

    path.setAttribute("d", pathData);
    path.setAttribute("stroke", "black");
    path.setAttribute("stroke-width", "2");
    path.setAttribute("fill", "none");
    svgElement.appendChild(path);
  }

  const svgWidth = 800;
  const svgHeight = 600;

  // On mount, draw the track based on the recordInputStore value
  onMount(() => {
    let carAngle = 0;
    const lineLengthMultiplier = 40;
    const trackPoints = [{ x: svgWidth / 2, y: svgHeight / 2 }];

    for (let i = 0; i < $recordInputStore.length; i++) {
      const { key, time } = $recordInputStore[i];

      let timeDifference = 0;
      if (i < $recordInputStore.length - 1) {
        timeDifference =
          ($recordInputStore[i + 1].time.getTime() - time.getTime()) / 1000;
      }

      const lineLength = timeDifference * lineLengthMultiplier;
      const startPoint = trackPoints[i];
      if (!startPoint) {
        console.error(`No track point found at index ${i}`);
        continue;
      }

      if (key === "n") {
        const endPoint = {
          x: startPoint.x + lineLength * Math.sin(carAngle * (Math.PI / 180)),
          y: startPoint.y - lineLength * Math.cos(carAngle * (Math.PI / 180)),
        };
        trackPoints.push(endPoint);
        drawStraightLine(startPoint, endPoint);
      } else if (key === "s") {
        const endPoint = {
          x: startPoint.x + lineLength * Math.sin(carAngle * (Math.PI / 180)),
          y: startPoint.y + lineLength * Math.cos(carAngle * (Math.PI / 180)),
        };
        trackPoints.push(endPoint);
        drawStraightLine(startPoint, endPoint);
      } else if (key === "ne") {
        const startPoint = trackPoints[i];
        const radius = 100;

        const arcAngle = lineLength / radius;

        const endPoint = {
          x: startPoint.x + radius * Math.cos(carAngle + arcAngle),
          y: startPoint.y - radius * Math.sin(carAngle + arcAngle),
        };

        carAngle += arcAngle;
        console.log(carAngle);

        trackPoints.push(endPoint);
        drawArc(startPoint, endPoint, radius);
      }
    }
  });
</script>

<!-- SVG element to draw the track -->
<svg
  bind:this={svgElement}
  width={svgWidth}
  height={svgHeight}
  style="border: 1px solid black; position: absolute; top: 50%; left: 50%; transform: translate(-50%, -50%);"
>
</svg>