#!/usr/bin/env python3

# Based on sol2 single header generator
# https://github.com/ThePhD/sol2/blob/develop/single/single.py
import argparse
import os, sys
import re
import datetime as dt

# python 3 compatibility
try:
	import cStringIO as sstream
except ImportError:
	from io import StringIO

description = "Single header file generator"

# command line parser
parser = argparse.ArgumentParser(usage='%(prog)s [options...]',
                                 description=description)
parser.add_argument(
    '--output',
    '-o',
    nargs='+',
    help=
    'name and location of where to place file (and forward declaration file)',
    metavar='file',
    default=['build/include/ranmath/ran.hpp'])
parser.add_argument('--input',
                    '-i',
                    help='the path to use to get to the project files',
                    metavar='path',
                    default=os.path.normpath(
                        os.path.dirname(os.path.realpath(__file__)) +
                        '/../include'))
parser.add_argument('--quiet', help='suppress all output', action='store_true')
args = parser.parse_args()

single_file = ''
forward_single_file = ''
single_file = os.path.normpath(args.output[0])

if len(args.output) > 1:
	forward_single_file = os.path.normpath(args.output[1])
else:
	a, b = os.path.splitext(single_file)
	a = os.path.dirname(single_file)
	forward_single_file = os.path.normpath(
	    os.path.join(a + '/', 'forward' + b))

single_file_dir = os.path.dirname(single_file)
forward_single_file_dir = os.path.dirname(forward_single_file)

script_path = os.path.normpath(args.input)
working_dir = os.getcwd()
os.chdir(script_path)

# If the user didn't provide absolute paths then construct them based on the current working dir.
if not os.path.isabs(single_file):
	single_file = os.path.join(working_dir, single_file)
	single_file_dir = os.path.join(working_dir, single_file_dir)

if not os.path.isabs(forward_single_file):
	forward_single_file = os.path.join(working_dir, forward_single_file)
	forward_single_file_dir = os.path.join(working_dir,
	                                       forward_single_file_dir)


intro = """#ifndef {guard}
#define {guard}

"""

includes = set([])
standard_include = re.compile(r'\s*#include <(.*?)>')
local_include = re.compile(r'\s*#(\s*?)include "(.*?)"')
project_include = re.compile(r'\s*#(\s*?)include <(ranmath/.*?)>')
pragma_once_cpp = re.compile(r'(\s*)#(\s*)pragma(\s+)once')
ifndef_cpp = re.compile(r'#ifndef RAN_.*?_HPP_')
define_cpp = re.compile(r'#define RAN_.*?_HPP_')
endif_cpp = re.compile(r'#endif // #ifndef RAN_.*?_HPP_')
forward_cpp = re.compile(r'RAN_FORWARD_HPP_')

def get_include(line, base_path):
	local_match = local_include.match(line)
	if local_match:
		# local include found
		full_path = os.path.normpath(
		    os.path.join(base_path,
		                 local_match.group(2))).replace('\\', '/')
		return full_path
	project_match = project_include.match(line)
	if project_match:
		# project-local include found
		full_path = os.path.normpath(
		    os.path.join(script_path,
		                 project_match.group(2))).replace('\\', '/')
		return full_path
	return None


def is_include_guard(line):
	is_regular_guard = ifndef_cpp.match(line) or define_cpp.match(
	    line) or endif_cpp.match(line) or pragma_once_cpp.match(line)
	if is_regular_guard:
		return not forward_cpp.search(
		    line) #and not forward_detail_cpp.search(line)
	return is_regular_guard


def get_revision():
	return os.popen('git rev-parse --short HEAD').read().strip()


def get_version():
	return os.popen('git describe --tags --abbrev=0').read().strip()


def process_file(filename, out):
	global includes
	filename = os.path.normpath(filename)
	relativefilename = filename.replace(script_path + os.sep,
	                                    "").replace("\\", "/")

	if filename in includes:
		return

	includes.add(filename)

	if not args.quiet:
		print('processing {}'.format(filename))

	out.write('// beginning of {}\n\n'.format(relativefilename))
	empty_line_state = True

	with open(filename, 'r', encoding='utf-8') as f:
		for line in f:
			# skip comments
			if line.startswith('//'):
				continue

			# skip include guard non-sense
			if is_include_guard(line):
				continue

			# get relative directory
			base_path = os.path.dirname(filename)

			# check if it's a standard file
			# TODO: this is FAR too aggressive and catches
			# includes and files not part of the standard (C includes)
			# and friends.
			# we should add a list of standard includes here??
			# or handle behavior differently...
			#std = standard_include.search(line)
			#if std:
			#	std_file = os.path.join('std', std.group(0))
			#	if std_file in includes:
			#		continue
			#	includes.add(std_file)

			# see if it's an include file
			name = get_include(line, base_path)

			if name:
				process_file(name, out)
				continue

			empty_line = len(line.strip()) == 0

			if empty_line and empty_line_state:
				continue

			empty_line_state = empty_line

			# line is fine
			out.write(line)

	out.write('// end of {}\n\n'.format(relativefilename))


version = get_version()
revision = get_revision()
include_guard = 'RAN_SINGLE_HPP_'
forward_include_guard = 'RAN_SINGLE_FORWARD_HPP_'

processed_files = [os.path.join(script_path, x) for x in ['ranmath/ran.hpp']]
forward_processed_files = [
    os.path.join(script_path, x) for x in ['ranmath/forward.hpp']
]
result = ''
forward_result = ''

if not args.quiet:
	print('Current version: {version} (revision {revision})\n'.format(
	    version=version, revision=revision))
	print('Creating single header')

ss = StringIO()
ss.write(
    intro.format(time=dt.datetime.utcnow(),
                 revision=revision,
                 version=version,
                 guard=include_guard))
for processed_file in processed_files:
	process_file(processed_file, ss)

ss.write('#endif // {}\n'.format(include_guard))
result = ss.getvalue()
ss.close()

if not args.quiet:
	print('finished creating single header\n')

if not args.quiet:
	print('Creating single forward declaration header')

includes = set([])
forward_ss = StringIO()
forward_ss.write(
    intro.format(time=dt.datetime.utcnow(),
                 revision=revision,
                 version=version,
                 guard=forward_include_guard))
for forward_processed_file in forward_processed_files:
	process_file(forward_processed_file, forward_ss)

forward_ss.write('#endif // {}\n'.format(forward_include_guard))
forward_result = forward_ss.getvalue()
forward_ss.close()

if not args.quiet:
	print('finished creating single forward declaration header\n')

# Create the output directories if they don't already exist.
os.makedirs(single_file_dir, exist_ok=True)
os.makedirs(forward_single_file_dir, exist_ok=True)

with open(single_file, 'w', encoding='utf-8') as f:
	if not args.quiet:
		print('writing {}...'.format(single_file))
	f.write(result)

with open(forward_single_file, 'w', encoding='utf-8') as f:
	if not args.quiet:
		print('writing {}...'.format(forward_single_file))
	f.write(forward_result)
