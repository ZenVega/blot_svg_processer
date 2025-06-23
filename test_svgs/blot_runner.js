const closePaths = (lines) =>
{
  return lines.map(line => {
    if (!line.length) return line;
    const first = line[0];
    const last = line[line.length - 1];
    const same =
      Math.abs(first[0] - last[0]) < 0.0001 &&
      Math.abs(first[1] - last[1]) < 0.0001;

    return same ? line : [...line, first];
  });
}


const width = 125;
const height = 125;

setDocDimensions(width, height);

//paste converted array into rawLines
const rawLines = [[[]]];
let finalLines = closePaths(rawLines);
  
drawLines(finalLines);
