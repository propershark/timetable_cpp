FROM alpine

# Copy sources.
COPY ./ /timetable
WORKDIR /timetable

# Install build tools.
RUN apk add --no-cache build-base cmake bash findutils

# Compile wamped library.
WORKDIR /timetable/wamped/build
RUN cmake ..
RUN make wamped 

# Link wamped static libs.
WORKDIR /timetable
RUN ln wamped/build/source/wamped/libwamped.a lib/libwamped.a
RUN ln wamped/build/source/mpackCPP/libmpackcpp.a lib/libmpackcpp.a
RUN ln wamped/build/mpack/src/mpack/libmpack.a lib/libmpack.a

# Compile timetable.
RUN make 

# Copy BART GTFS data.
ADD https://www.bart.gov/sites/default/files/docs/google_transit_20170612_v1.zip /timetable/data.zip 
RUN mkdir data && unzip data.zip -d data && rm data.zip

ENTRYPOINT bin/release/timetable -t ws://crossbar:8080/ws data
